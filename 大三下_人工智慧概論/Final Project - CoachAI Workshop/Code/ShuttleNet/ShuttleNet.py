import torch
import torch.nn as nn
import torch.nn.functional as F
from ShuttleNet.ShuttleNet_layers import EncoderLayer, DecoderLayer, GatedFusionLayer
from ShuttleNet.ShuttleNet_embedding import PositionalEncoding, PlayerEmbedding, ShotEmbedding, Embedding

PAD = 0


def get_pad_mask(seq):
    return (seq != PAD).unsqueeze(-2)


def get_subsequent_mask(seq):
    ''' For masking out the subsequent info. '''
    sz_b, len_s = seq.size()
    subsequent_mask = (1 - torch.triu(
        torch.ones((1, len_s, len_s), device=seq.device), diagonal=1)).bool()
    return subsequent_mask


def alternatemerge(seq_A, seq_B, merge_len, player):
    # (batch, seq_len, dim)
    seq_len = seq_A.shape[1]
    merged_seq = torch.zeros(seq_A.shape[0], merge_len, seq_A.shape[2])

    if seq_len * 2 == (merge_len - 1):
        # if seq_len is odd and B will shorter, e.g., merge = 5, A = 3, B = 2
        merged_seq[:, 1::2, :] = seq_A[:, :seq_len, :]
        merged_seq[:, 2::2, :] = seq_B[:, :seq_len, :]
    elif (seq_len * 2 - 1) == merge_len:
        # if seq_len is odd and A will longer, e.g., merge = 5, A = 3, B = 2
        merged_seq[:, ::2, :] = seq_A[:, :seq_len, :]
        merged_seq[:, 1::2, :] = seq_B[:, :merge_len - seq_len, :]
    elif seq_len * 2 == merge_len:
        if player == 'A':
            merged_seq[:, ::2, :] = seq_A[:, :seq_len, :]
            merged_seq[:, 1::2, :] = seq_B[:, :seq_len, :]
        elif player == 'B':
            merged_seq[:, 1::2, :] = seq_A[:, :seq_len, :]
            merged_seq[:, 2::2, :] = seq_B[:, :seq_len - 1, :]
        else:
            raise NotImplementedError
    else:
        raise NotImplementedError

    return merged_seq.to(seq_A.device)


class ShotGenDecoder(nn.Module):
    def __init__(self, config, feature_name):
        super().__init__()
        self.feature_embedding = dict()
        #print(config['shot_num'], config['player_num'])
        feature_name = feature_name[:-3]
        for key in feature_name:
            if key == 'landing_x' or key == 'landing_y' or\
               key == 'time_diff' or key == 'shot_angle' or\
               key == 'distance':
                continue
            num = key + "_num"
            if key== 'type':
                num = 'shot' + "_num"
            self.feature_embedding[key] = Embedding(config[num], config['var_dim'])

        self.feature_embedding['area'] = nn.Linear(2, config['area_dim'])
        self.feature_embedding['time_diff'] = nn.Linear(1, config['area_dim'])
        self.feature_embedding['shot_angle'] = nn.Linear(1, config['area_dim'])
        self.feature_embedding['distance'] = nn.Linear(1, config['area_dim'])


        #self.area_embedding = nn.Linear(2, config['area_dim'])
        #self.shot_embedding = ShotEmbedding(config['shot_num'], config['shot_dim'])
        #self.player_embedding = PlayerEmbedding(config['player_num'], config['player_dim'])

        n_heads = 2
        d_k = config['encode_dim']
        d_v = config['encode_dim']
        d_model = config['encode_dim']
        d_inner = config['encode_dim'] * 2
        dropout = 0.1
        self.d_model = d_model

        self.position_embedding = PositionalEncoding(config['shot_dim'], config['encode_length'],
                                                     n_position=config['max_ball_round'] + 1)
        self.dropout = nn.Dropout(p=dropout)

        self.global_layer = DecoderLayer(d_model, d_inner, n_heads, d_k, d_v, dropout=dropout)
        self.local_layer = DecoderLayer(d_model, d_inner, n_heads, d_k, d_v, dropout=dropout)

        self.gated_fusion = GatedFusionLayer(d_model, d_model, config['encode_length'], config['max_ball_round'] + 1)

    def forward(self, input_dict, encode_local_output, encode_global_A, encode_global_B,
                trg_mask=None, return_attns=False):
        decoder_self_attention_list, decoder_encoder_self_attention_list = [], []
        

        area = torch.cat((input_dict['landing_x'].unsqueeze(-1), input_dict['landing_y'].unsqueeze(-1)), dim=-1).float()
        time_diff = input_dict['time_diff'].unsqueeze(-1).float()
        shot_angle = input_dict['shot_angle'].unsqueeze(-1).float()
        distance = input_dict['distance'].unsqueeze(-1).float()

        # area = torch.cat((input_x.unsqueeze(-1), input_y.unsqueeze(-1)), dim=-1).float()
        # area = torch.cat((input_dict['landing_x'].unsqueeze(-1), input_dict['landing_y'].unsqueeze(-1)), dim=-1).float()

        # split player only for masking
        mask_A_dict  = dict()
        mask_B_dict  = dict()
        for key in input_dict.keys():            
            if key == 'landing_x' or key == 'landing_y' or\
               key == 'time_diff' or key == 'shot_angle' or\
               key == 'distance' or key == 'area':
                continue
            mask_A_dict[key] = input_dict[key][:, ::2]
            mask_B_dict[key] = input_dict[key][:, 1::2]
        
        # mask_A = input_dict['type'][:, ::2]
        # mask_B = input_dict['type'][:, 1::2]

        # triangular mask
        for key in input_dict.keys():            
            if key == 'landing_x' or key == 'landing_y' or\
               key == 'time_diff' or key == 'shot_angle' or\
               key == 'distance' or key == 'area':
                continue
            trg_local_mask = get_pad_mask(input_dict[key]) & get_subsequent_mask(input_dict[key])
            trg_global_A_mask = get_pad_mask(mask_A_dict[key]) & get_subsequent_mask(mask_A_dict[key])
            trg_global_B_mask = get_pad_mask(mask_B_dict[key]) & get_subsequent_mask(mask_B_dict[key])

        #trg_local_mask = get_pad_mask(input_dict['type']) & get_subsequent_mask(input_dict['type'])
        #trg_global_A_mask = get_pad_mask(mask_A) & get_subsequent_mask(mask_A)
        #trg_global_B_mask = get_pad_mask(mask_B) & get_subsequent_mask(mask_B)


        embedded_dict = dict()
        embedded_dict['area'] = F.relu(self.feature_embedding['area'](area))
        embedded_dict['time_diff'] = F.relu(self.feature_embedding['time_diff'](time_diff))
        embedded_dict['shot_angle'] = F.relu(self.feature_embedding['shot_angle'](shot_angle))
        embedded_dict['distance'] = F.relu(self.feature_embedding['distance'](distance))
        for key in input_dict.keys():            
            if key == 'landing_x' or key == 'landing_y' or\
               key == 'time_diff' or key == 'shot_angle' or\
               key == 'distance' or key == 'area':
                continue
            embedded_dict[key] = self.feature_embedding[key](input_dict[key].to(torch.int64))
        # embedded_player = self.player_embedding(input_player)

        h_a = embedded_dict['area']
        h_s = embedded_dict['type']
        for key in embedded_dict.keys():
            if key == 'area' or key == 'type':
                continue
            h_a = h_a + embedded_dict[key]
            h_s = h_s + embedded_dict[key]

        # split player

        h_a_A = h_a[:, ::2]
        h_a_B = h_a[:, 1::2]
        h_s_A = h_s[:, ::2]
        h_s_B = h_s[:, 1::2]
        # local
        decode_output_area = self.dropout(self.position_embedding(h_a, mode='decode'))
        decode_output_shot = self.dropout(self.position_embedding(h_s, mode='decode'))
        # global
        decode_output_area_A = self.dropout(self.position_embedding(h_a_A, mode='decode'))
        decode_output_area_B = self.dropout(self.position_embedding(h_a_B, mode='decode'))
        decode_output_shot_A = self.dropout(self.position_embedding(h_s_A, mode='decode'))
        decode_output_shot_B = self.dropout(self.position_embedding(h_s_B, mode='decode'))

        decode_global_A, dec_slf_attn_A, dec_enc_attn_A, disentangled_weight_A = self.global_layer(decode_output_area_A,
                                                                                                   decode_output_shot_A,
                                                                                                   encode_global_A,
                                                                                                   slf_attn_mask=trg_global_A_mask,
                                                                                                   return_attns=return_attns)
        if decode_output_area_B.shape[1] != 0:
            decode_global_B, dec_slf_attn_B, dec_enc_attn_B, disentangled_weight_B = self.global_layer(
                decode_output_area_B, decode_output_shot_B, encode_global_B, slf_attn_mask=trg_global_B_mask,
                return_attns=return_attns)

        decode_local_output, dec_slf_attn, dec_enc_attn, disentangled_weight_local = self.local_layer(
            decode_output_area, decode_output_shot, encode_local_output, slf_attn_mask=trg_local_mask,
            return_attns=return_attns)
        decoder_self_attention_list = dec_slf_attn if return_attns else []
        decoder_encoder_self_attention_list = dec_enc_attn if return_attns else []

        if decode_output_area_B.shape[1] != 0:
            decode_output_A = alternatemerge(decode_global_A, decode_global_A, decode_local_output.shape[1], 'A')
            decode_output_B = alternatemerge(decode_global_B, decode_global_B, decode_local_output.shape[1], 'B')
        else:
            decode_output_A = decode_global_A.clone()
            decode_output_B = torch.zeros(decode_local_output.shape, device=decode_local_output.device)
        decode_output = self.gated_fusion(decode_output_A, decode_output_B, decode_local_output)
        # (batch, seq_len, encode_dim)
        if return_attns:
            return decode_output, decoder_self_attention_list, decoder_encoder_self_attention_list, disentangled_weight_local
        return decode_output


class ShotGenPredictor(nn.Module):
    def __init__(self, config, feature_name):
        super().__init__()
        self.shotgen_decoder = ShotGenDecoder(config, feature_name)
        self.area_decoder = nn.Sequential(
            nn.Linear(config['encode_dim'], config['area_num'], bias=False)
        )
        self.shot_decoder = nn.Sequential(
            nn.Linear(config['encode_dim'], config['shot_num'], bias=False)
        )
        self.player_embedding = PlayerEmbedding(config['player_num'], config['player_dim'])

    def forward(self, input_dict, encode_local_output, encode_global_A, encode_global_B,
                target_player, return_attns=False):
        embedded_target_player = self.player_embedding(target_player)
        if return_attns:
            decode_output, decoder_self_attention_list, decoder_encoder_self_attention_list, disentangled_weight_local = self.shotgen_decoder(
                input_dict, encode_local_output, encode_global_A, encode_global_B, return_attns=return_attns)
        else:
            decode_output = self.shotgen_decoder(input_dict, encode_local_output, encode_global_A, encode_global_B, return_attns)

        decode_output = (decode_output + embedded_target_player)

        area_logits = self.area_decoder(decode_output)
        shot_logits = self.shot_decoder(decode_output)


        if return_attns:
            return area_logits, shot_logits, decoder_self_attention_list, decoder_encoder_self_attention_list, disentangled_weight_local
        else:
            return area_logits, shot_logits


class ShotGenEncoder(nn.Module):
    def __init__(self, config, feature_name):
        super().__init__()
        self.feature_embedding = dict()
        # print(config['shot_num'], config['player_num'])
        feature_name = feature_name[:-3]
        
        for key in feature_name:
            if key == 'landing_x' or key == 'landing_y' or\
               key == 'time_diff' or key == 'shot_angle' or\
               key == 'distance':
                continue
            num = key + "_num"
            if key== 'type':
                num = 'shot' + "_num"
            self.feature_embedding[key] = Embedding(config[num], config['var_dim'])

        self.feature_embedding['area'] = nn.Linear(2, config['area_dim'])
        self.feature_embedding['time_diff'] = nn.Linear(1, config['area_dim'])
        self.feature_embedding['shot_angle'] = nn.Linear(1, config['area_dim'])
        self.feature_embedding['distance'] = nn.Linear(1, config['area_dim'])

        # self.shot_embedding = ShotEmbedding(config['shot_num'], config['shot_dim'])
        # self.player_embedding = PlayerEmbedding(config['player_num'], config['player_dim'])

        n_heads = 2
        d_k = config['encode_dim']
        d_v = config['encode_dim']
        d_model = config['encode_dim']
        d_inner = config['encode_dim'] * 2
        dropout = 0.1
        self.d_model = d_model

        self.position_embedding = PositionalEncoding(config['shot_dim'], config['encode_length'],
                                                     n_position=config['max_ball_round'])
        self.dropout = nn.Dropout(p=dropout)

        self.global_layer = EncoderLayer(d_model, d_inner, n_heads, d_k, d_v, dropout=dropout)
        self.local_layer = EncoderLayer(d_model, d_inner, n_heads, d_k, d_v, dropout=dropout)


    def forward(self, input_dict, src_mask=None, return_attns=False):
        enc_slf_attn_list = []
        area = torch.cat((input_dict['landing_x'].unsqueeze(-1), input_dict['landing_y'].unsqueeze(-1)), dim=-1).float()
        time_diff = input_dict['time_diff'].unsqueeze(-1).float()
        shot_angle = input_dict['shot_angle'].unsqueeze(-1).float()
        distance = input_dict['distance'].unsqueeze(-1).float()
        # area = torch.cat((input_x.unsqueeze(-1), input_y.unsqueeze(-1)), dim=-1).float()

        # embedded_area = F.relu(self.area_embedding(area))
        embedded_dict = dict()
        embedded_dict['area'] = F.relu(self.feature_embedding['area'](area))
        embedded_dict['time_diff'] = F.relu(self.feature_embedding['time_diff'](time_diff))
        embedded_dict['shot_angle'] = F.relu(self.feature_embedding['shot_angle'](shot_angle))
        embedded_dict['distance'] = F.relu(self.feature_embedding['distance'](distance))
        for key in input_dict.keys():          

            if key == 'landing_x' or key == 'landing_y' or\
               key == 'time_diff' or key == 'shot_angle' or\
               key == 'distance' or key == 'area':
                continue
            embedded_dict[key] = self.feature_embedding[key](input_dict[key].to(torch.int64))
        # embedded_player = self.player_embedding(input_player)

        h_a = embedded_dict['area']
        h_s = embedded_dict['type']
        for key in embedded_dict.keys():
            if key == 'area' or key == 'type':
                continue
            h_a = h_a + embedded_dict[key]
            h_s = h_s + embedded_dict[key]
        # split player

        h_a_A = h_a[:, ::2]
        h_a_B = h_a[:, 1::2]
        h_s_A = h_s[:, ::2]
        h_s_B = h_s[:, 1::2]


        # local
        encode_output_area = self.dropout(self.position_embedding(h_a, mode='encode'))
        encode_output_shot = self.dropout(self.position_embedding(h_s, mode='encode'))

        # global
        encode_output_area_A = self.dropout(self.position_embedding(h_a_A, mode='encode'))
        encode_output_area_B = self.dropout(self.position_embedding(h_a_B, mode='encode'))
        encode_output_shot_A = self.dropout(self.position_embedding(h_s_A, mode='encode'))
        encode_output_shot_B = self.dropout(self.position_embedding(h_s_B, mode='encode'))

        encode_global_A, enc_slf_attn_A = self.global_layer(encode_output_area_A, encode_output_shot_A,
                                                            slf_attn_mask=src_mask)
        encode_global_B, enc_slf_attn_B = self.global_layer(encode_output_area_B, encode_output_shot_B,
                                                            slf_attn_mask=src_mask)
        encode_local_output, enc_slf_attn = self.local_layer(encode_output_area, encode_output_shot,
                                                             slf_attn_mask=src_mask)
        if return_attns:
            return encode_local_output, encode_global_A, encode_global_B, enc_slf_attn_list
        return encode_local_output, encode_global_A, encode_global_B
