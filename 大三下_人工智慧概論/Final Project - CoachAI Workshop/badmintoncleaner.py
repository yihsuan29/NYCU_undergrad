from torch.utils.data import DataLoader
from torch.utils.data import Dataset
import pandas as pd
import numpy as np
from datetime import datetime

pd.options.mode.chained_assignment = None

PAD = 0


class BadmintonDataset(Dataset):
    def __init__(self, matches, config):
        super().__init__()
        self.max_ball_round = config['max_ball_round']
        self.feature_selected = ['type', 'landing_x', 'landing_y', 'player',
                                 'roundscore_A', 'roundscore_B',
                                 'aroundhead', 'backhand', 'landing_height',
                                 'landing_area', 'player_location_area', 'player_location_x', 'player_location_y',
                                 'opponent_location_area', 'opponent_location_x', 'opponent_location_y', 'rally_id',
                                 'set', 'ball_round']

        group = matches[self.feature_selected] \
            .groupby('rally_id') \
            .apply(lambda r: (r['ball_round'].values, r['type'].values, r['landing_x'].values,
                              r['landing_y'].values, r['player'].values, r['set'].values,
                              r['roundscore_A'].values, r['roundscore_B'].values,
                              r['aroundhead'].values, r['backhand'].values, r['landing_height'].values,
                              r['landing_area'].values, r['player_location_area'].values, r['player_location_x'].values,
                              r['player_location_y'].values, r['opponent_location_area'].values,
                              r['opponent_location_x'].values, r['opponent_location_y'].values))

        self.sequences, self.rally_ids = {}, []

        for i, rally_id in enumerate(group.index):
            ball_round, shot_type, landing_x, landing_y, player, sets, \
                roundscore_A, roundscore_B, aroundhead, backhand, \
                landing_height, landing_area, player_location_area, \
                player_location_x, player_location_y, opponent_location_area, \
                opponent_location_x, opponent_location_y = group[rally_id]


            landing_height = landing_height- 1
            player_location_x = player_location_x / 100 - 2
            player_location_y = player_location_y / 200 - 2
            opponent_location_x = opponent_location_x / 100 - 2
            opponent_location_y = opponent_location_y / 200 - 2

            self.sequences[rally_id] = (ball_round, shot_type, landing_x, landing_y, player, sets,
                                        roundscore_A, roundscore_B, aroundhead, backhand,
                                        landing_height, landing_area, player_location_area,
                                        player_location_x, player_location_y, opponent_location_area,
                                        opponent_location_x, opponent_location_y)

            self.rally_ids.append(rally_id)

    def __len__(self):
        return len(self.sequences)

    def __getitem__(self, index):
        # 可改 加columns
        # around head -> 繞頭 
        # back hand -> 反手 -> 可排除攻擊
        # landing height -> 高於網比較有可能是攻擊
        rally_id = self.rally_ids[index]
        ball_round, shot_type, landing_x, landing_y, player, sets, \
            roundscore_A, roundscore_B, aroundhead, backhand, \
            landing_height, landing_area, player_location_area, \
            player_location_x, player_location_y, opponent_location_area, \
            opponent_location_x, opponent_location_y = self.sequences[rally_id]

        pad_input_shot = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        pad_input_x = np.full(self.max_ball_round, fill_value=PAD, dtype=float)
        pad_input_y = np.full(self.max_ball_round, fill_value=PAD, dtype=float)
        pad_input_player = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        pad_output_shot = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        pad_output_x = np.full(self.max_ball_round, fill_value=PAD, dtype=float)
        pad_output_y = np.full(self.max_ball_round, fill_value=PAD, dtype=float)
        pad_output_player = np.full(self.max_ball_round, fill_value=PAD, dtype=int)

        pad_roundscore_A = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        pad_roundscore_B = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        pad_aroundhead = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        pad_backhand = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        pad_landing_height = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        pad_landing_area = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        pad_player_location_area = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        pad_player_location_x = np.full(self.max_ball_round, fill_value=PAD, dtype=float)
        pad_player_location_y = np.full(self.max_ball_round, fill_value=PAD, dtype=float)
        pad_opponent_location_area = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        pad_opponent_location_x = np.full(self.max_ball_round, fill_value=PAD, dtype=float)
        pad_opponent_location_y = np.full(self.max_ball_round, fill_value=PAD, dtype=float)

        # pad or trim based on the max ball round
        # 可改 要把資料寫進去
        # 加入features
        # e.g. 兩人站位的距離 角度之類的 (感覺就會打對手接不到的位置)
        if len(ball_round) > self.max_ball_round:
            rally_len = self.max_ball_round

            # input
            pad_input_shot[:] = shot_type[0:-1:1][:rally_len]  # 0, 1, ..., max_ball_round-1
            pad_input_x[:] = landing_x[0:-1:1][:rally_len]
            pad_input_y[:] = landing_y[0:-1:1][:rally_len]
            pad_input_player[:] = player[0:-1:1][:rally_len]
            pad_roundscore_A[:] = roundscore_A[0:-1:1][:rally_len]
            pad_roundscore_B[:] = roundscore_B[0:-1:1][:rally_len]
            pad_aroundhead[:] = aroundhead[0:-1:1][:rally_len]
            pad_backhand[:] = backhand[0:-1:1][:rally_len]
            pad_landing_height[:] = landing_height[0:-1:1][:rally_len]
            pad_landing_area[:] = landing_area[0:-1:1][:rally_len]
            pad_player_location_area[:] = player_location_area[0:-1:1][:rally_len]
            pad_player_location_x[:] = player_location_x[0:-1:1][:rally_len]
            pad_player_location_y[:] = player_location_y[0:-1:1][:rally_len]
            pad_opponent_location_area[:] = opponent_location_area[0:-1:1][:rally_len]  # 0, 1, ..., max_ball_round-1
            pad_opponent_location_x[:] = opponent_location_x[0:-1:1][:rally_len]
            pad_opponent_location_y[:] = opponent_location_y[0:-1:1][:rally_len]
            # output
            pad_output_shot[:] = shot_type[1::1][:rally_len]  # 1, 2, ..., max_ball_round
            pad_output_x[:] = landing_x[1::1][:rally_len]
            pad_output_y[:] = landing_y[1::1][:rally_len]
            pad_output_player[:] = player[1::1][:rally_len]

        else:
            # input
            rally_len = len(ball_round) - 1
            pad_input_shot[:rally_len] = shot_type[0:-1:1]  # 0, 1, ..., n-1
            pad_input_x[:rally_len] = landing_x[0:-1:1]
            pad_input_y[:rally_len] = landing_y[0:-1:1]
            pad_input_player[:rally_len] = player[0:-1:1]
            pad_roundscore_A[:rally_len] = roundscore_A[0:-1:1]
            pad_roundscore_B[:rally_len] = roundscore_B[0:-1:1]
            pad_aroundhead[:rally_len] = aroundhead[0:-1:1]
            pad_backhand[:rally_len] = backhand[0:-1:1]
            pad_landing_height[:rally_len] = landing_height[0:-1:1]
            pad_landing_area[:rally_len] = landing_area[0:-1:1]
            pad_player_location_area[:rally_len] = player_location_area[0:-1:1]
            pad_player_location_x[:rally_len] = player_location_x[0:-1:1]
            pad_player_location_y[:rally_len] = player_location_y[0:-1:1]
            pad_opponent_location_area[:rally_len] = opponent_location_area[0:-1:1]  # 0, 1, ..., max_ball_round-1
            pad_opponent_location_x[:rally_len] = opponent_location_x[0:-1:1]
            pad_opponent_location_y[:rally_len] = opponent_location_y[0:-1:1]
            # output
            pad_output_shot[:rally_len] = shot_type[1::1]  # 1, 2, ..., n
            pad_output_x[:rally_len] = landing_x[1::1]
            pad_output_y[:rally_len] = landing_y[1::1]
            pad_output_player[:rally_len] = player[1::1]

        # print(type(pad_time[0]),type(pad_input_shot[0]))
        return (pad_input_shot, pad_input_x, pad_input_y, pad_input_player,
                pad_roundscore_A, pad_roundscore_B, pad_aroundhead,
                pad_backhand, pad_landing_height, pad_landing_area,
                pad_player_location_area, pad_player_location_x,
                pad_player_location_y, pad_opponent_location_area,
                pad_opponent_location_x, pad_opponent_location_y,
                pad_output_shot, pad_output_x, pad_output_y, pad_output_player,
                rally_len, sets[0])


"""
        
                
"""


def prepare_dataset(config):
    train_matches = pd.read_csv(f"{config['data_folder']}train.csv")
    val_matches = pd.read_csv(f"{config['data_folder']}val_given.csv")
    test_matches = pd.read_csv(f"{config['data_folder']}test_given.csv")
    # encode shot type
    codes_type, uniques_type = pd.factorize(train_matches['type'])
    train_matches['type'] = codes_type + 1  # Reserve code 0 for paddings
    val_matches['type'] = val_matches['type'].apply(lambda x: list(uniques_type).index(x) + 1)
    test_matches['type'] = test_matches['type'].apply(lambda x: list(uniques_type).index(x) + 1)
    config['uniques_type'] = uniques_type.to_list()
    config['shot_num'] = len(uniques_type) + 1  # Add padding

    # encode player
    train_matches['player'] = train_matches['player'].apply(lambda x: x + 1)
    val_matches['player'] = val_matches['player'].apply(lambda x: x + 1)
    test_matches['player'] = test_matches['player'].apply(lambda x: x + 1)
    config['player_num'] = 35 + 1  # Add padding

    # encode other variable
    config['roundscore_A_num'] = 26 + 1
    config['roundscore_B_num'] = 26 + 1
    config['aroundhead_num'] = 2 + 1
    config['backhand_num'] = 2 + 1
    config['landing_height_num'] = 2 + 1
    config['landing_area_num'] = 9 + 1
    config['player_location_area'] = 9 + 1
    config['opponent_location_area'] = 9 + 1

    config['var_dim'] = 32


    val_matches['landing_height'] = val_matches['landing_height']- 1
    val_matches['player_location_x'] = val_matches['player_location_x']  / 100 - 2
    val_matches['player_location_y'] = val_matches['player_location_y']  / 200 - 2
    val_matches['opponent_location_x']  = val_matches['opponent_location_x'] / 100 - 2
    val_matches['opponent_location_y']  = val_matches['opponent_location_y']  / 200 - 2

    train_dataset = BadmintonDataset(train_matches, config)
    feature_name = train_dataset.feature_selected
    # del feature_name['rally_id']
    # del feature_name['set']
    # del feature_name['ball_round']
    train_dataloader = DataLoader(train_dataset, batch_size=config['batch_size'], shuffle=True)

    val_dataset = BadmintonDataset(val_matches, config)
    val_dataloader = DataLoader(val_dataset, batch_size=config['batch_size'], shuffle=False)
    test_dataset = BadmintonDataset(test_matches, config)
    test_dataloader = DataLoader(test_dataset, batch_size=config['batch_size'], shuffle=False)
    return config, train_dataloader, val_dataloader, test_dataloader, train_matches, val_matches, test_matches, feature_name