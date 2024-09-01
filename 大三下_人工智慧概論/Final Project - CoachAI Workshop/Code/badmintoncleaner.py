from torch.utils.data import DataLoader
from torch.utils.data import Dataset
import pandas as pd
import numpy as np
from datetime import datetime
import math

pd.options.mode.chained_assignment = None

PAD = 0

def calculate_angle(player_x, player_y, opponent_x, opponent_y):
    diff_x = opponent_x - player_x
    diff_y = opponent_y - player_x
    rad_angle = math.atan2(diff_y, diff_x)
    degree_angle = math.degrees(rad_angle)
    if degree_angle < 0:
        degree_angle += 360
    return degree_angle

class BadmintonDataset(Dataset):
    def __init__(self, matches, config):
        super().__init__()
        self.max_ball_round = config['max_ball_round']
        # self.feature_selected = ['type', 'landing_x', 'landing_y', 'player',
        #                          'roundscore_A', 'roundscore_B',
        #                          'aroundhead', 'backhand', 'landing_height',
        #                          'landing_area', 'player_location_area', 'player_location_x', 'player_location_y',
        #                          'opponent_location_area', 'opponent_location_x', 'opponent_location_y', 'rally_id',
        #                          'set', 'ball_round']
        
        self.feature_selected = ['type', 'landing_x', 'landing_y', 'player',
                                 'score_diff','time_diff',
                                 'aroundhead', 'backhand', 'landing_height',
                                 'shot_angle','distance', 
                                 'x_distance','y_distance',
                                 'rally_id',
                                 'set', 'ball_round']

        # group = matches[self.feature_selected] \
        #     .groupby('rally_id') \
        #     .apply(lambda r: (r['ball_round'].values, r['type'].values, r['landing_x'].values,
        #                       r['landing_y'].values, r['player'].values, r['set'].values,
        #                       r['roundscore_A'].values, r['roundscore_B'].values,
        #                       r['aroundhead'].values, r['backhand'].values, r['landing_height'].values,
        #                       r['landing_area'].values, r['player_location_area'].values, r['player_location_x'].values,
        #                       r['player_location_y'].values, r['opponent_location_area'].values,
        #                       r['opponent_location_x'].values, r['opponent_location_y'].values))
        group = matches[self.feature_selected] \
            .groupby('rally_id') \
            .apply(lambda r: (r['ball_round'].values, r['type'].values, r['landing_x'].values,
                              r['landing_y'].values, r['player'].values, r['set'].values,
                              r['score_diff'].values, r['time_diff'].values,
                              r['aroundhead'].values, r['backhand'].values, r['landing_height'].values,
                              r['shot_angle'].values, r['distance'].values, 
                              r['x_distance'].values, r['y_distance'].values))

        self.sequences, self.rally_ids = {}, []

        for i, rally_id in enumerate(group.index):
#             ball_round, shot_type, landing_x, landing_y, player, sets, \
#                 roundscore_A, roundscore_B, aroundhead, backhand, \
#                 landing_height, landing_area, player_location_area, \
#                 player_location_x, player_location_y, opponent_location_area, \
#                 opponent_location_x, opponent_location_y = group[rally_id]

#             self.sequences[rally_id] = (ball_round, shot_type, landing_x, landing_y, player, sets,
#                                         roundscore_A, roundscore_B, aroundhead, backhand,
#                                         landing_height, landing_area, player_location_area,
#                                         player_location_x, player_location_y, opponent_location_area,
#                                         opponent_location_x, opponent_location_y)
            ball_round, shot_type, landing_x, landing_y, player, sets, \
            score_diff, time_diff, aroundhead, backhand, \
            landing_height, shot_angle, distance, x_distance, y_distance = group[rally_id]

            self.sequences[rally_id] = (ball_round, shot_type, landing_x, landing_y, player, sets, 
                                        score_diff, time_diff, aroundhead, backhand, 
                                        landing_height, shot_angle, distance, x_distance, y_distance)

            self.rally_ids.append(rally_id)

    def __len__(self):
        return len(self.sequences)

    def __getitem__(self, index):
        # 可改 加columns
        # around head -> 繞頭 
        # back hand -> 反手 -> 可排除攻擊
        # landing height -> 高於網比較有可能是攻擊
        rally_id = self.rally_ids[index]
        # ball_round, shot_type, landing_x, landing_y, player, sets, \
        #     roundscore_A, roundscore_B, aroundhead, backhand, \
        #     landing_height, landing_area, player_location_area, \
        #     player_location_x, player_location_y, opponent_location_area, \
        #     opponent_location_x, opponent_location_y = self.sequences[rally_id]
        
        ball_round, shot_type, landing_x, landing_y, player, sets, \
        score_diff, time_diff, aroundhead, backhand, \
        landing_height, shot_angle, distance, x_distance, y_distance = self.sequences[rally_id]

        pad_input_shot = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        pad_input_x = np.full(self.max_ball_round, fill_value=PAD, dtype=float)
        pad_input_y = np.full(self.max_ball_round, fill_value=PAD, dtype=float)
        pad_input_player = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        pad_output_shot = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        pad_output_x = np.full(self.max_ball_round, fill_value=PAD, dtype=float)
        pad_output_y = np.full(self.max_ball_round, fill_value=PAD, dtype=float)
        pad_output_player = np.full(self.max_ball_round, fill_value=PAD, dtype=int)

        pad_score_diff = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        pad_time_diff = np.full(self.max_ball_round, fill_value=PAD, dtype=float)
        pad_aroundhead = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        pad_backhand = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        pad_landing_height = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        
        pad_shot_angle = np.full(self.max_ball_round, fill_value=PAD, dtype=float)
        pad_distance = np.full(self.max_ball_round, fill_value=PAD, dtype=float)
        pad_x_distance = np.full(self.max_ball_round, fill_value=PAD, dtype=int)
        pad_y_distance = np.full(self.max_ball_round, fill_value=PAD, dtype=int)


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
            pad_score_diff[:] = score_diff[0:-1:1][:rally_len]
            pad_time_diff[:] = time_diff[0:-1:1][:rally_len]
            pad_aroundhead[:] = aroundhead[0:-1:1][:rally_len]
            pad_backhand[:] = backhand[0:-1:1][:rally_len]
            pad_landing_height[:] = landing_height[0:-1:1][:rally_len]
            
            pad_shot_angle[:] = shot_angle[0:-1:1][:rally_len]
            pad_distance[:] = distance[0:-1:1][:rally_len]
            pad_x_distance[:] = x_distance[0:-1:1][:rally_len]
            pad_y_distance[:] = y_distance[0:-1:1][:rally_len]

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
            pad_score_diff[:rally_len] = score_diff[0:-1:1]
            pad_time_diff[:rally_len] = time_diff[0:-1:1]
            pad_aroundhead[:rally_len] = aroundhead[0:-1:1]
            pad_backhand[:rally_len] = backhand[0:-1:1]
            pad_landing_height[:rally_len] = landing_height[0:-1:1]
            
            pad_shot_angle[:rally_len] = shot_angle[0:-1:1]
            pad_distance[:rally_len] = distance[0:-1:1]
            pad_x_distance[:rally_len] = x_distance[0:-1:1]
            pad_y_distance[:rally_len] = y_distance[0:-1:1]
            
            # output
            pad_output_shot[:rally_len] = shot_type[1::1]  # 1, 2, ..., n
            pad_output_x[:rally_len] = landing_x[1::1]
            pad_output_y[:rally_len] = landing_y[1::1]
            pad_output_player[:rally_len] = player[1::1]

        # print(type(pad_time[0]),type(pad_input_shot[0]))
        return (pad_input_shot, pad_input_x, pad_input_y, pad_input_player,
                pad_score_diff, pad_time_diff, pad_aroundhead,
                pad_backhand, pad_landing_height, pad_shot_angle,
                pad_distance, pad_x_distance, pad_y_distance,
                pad_output_shot, pad_output_x, pad_output_y, pad_output_player,
                rally_len, sets[0])


"""
        
                
"""
def feature_extraction(data):

    data['landing_height'] = data['landing_height'].fillna(1)
    data['landing_height'] = (data['landing_height']-1).astype(int)
    data['player_location_x'] =  data['player_location_x']  / 100 - 2
    data['player_location_y'] =  data['player_location_y']  / 200 - 2
    data['opponent_location_x']  = data['opponent_location_x'] / 100 - 2
    data['opponent_location_y']  = data['opponent_location_y']  / 200 - 2 
    
     # 1.distance
    data['distance'] = ((data['player_location_x']-data['opponent_location_x'])**2 + (data['player_location_y']-data['opponent_location_y'])**2)**0.5

    # 2.time difference
    data['date_time'] = pd.to_datetime(data['time'])
    time_diff = data['date_time'].diff()
    data['time_diff'] = time_diff.dt.total_seconds()
    data['time_diff'] = data['time_diff'].fillna(0)
    data['time_diff'].apply(lambda x: 0 if x<0 else x)

    # 3.shot angle
    data['shot_angle'] = data.apply(lambda row: calculate_angle(row['player_location_x'], row['player_location_y'], row['opponent_location_x'], row['opponent_location_y']), axis=1)



    # 4. difference between player_location_x and opponent location_x (x-axis distance)
    data['location_difference_x'] = abs(data['player_location_x']-data['opponent_location_x'])


    # 5. difference between player_location_y and opponent location_y(y-axis distance)
    data['location_difference_y'] = abs(data['player_location_y'] - data['opponent_location_y'])
    
    # 6. do classification on the distance on x-axis and y-axis
    # for y-axis , dy>400 -> 2(far), 236 < dy < 400 -> 1(not near nor far) , otherwise 0(near). 236 is the distance of double short service line, 400 is the half of the court.
    # for x-axis , dx>38  -> 1 (slanting angle) , otherwise -> 0 ( straight angle)  (38 is the boundary of some ball type appear or not)
    data['y_distance'] = np.where(data['location_difference_y'] > 400, 2, np.where((236 < data['location_difference_y']) & (data['location_difference_y'] < 400), 1, 0))
    data['x_distance'] = np.where(data['location_difference_x'] > 38, 1, 0)

    
    # 7. score diff
    data['score_diff'] = data['roundscore_A']-data['roundscore_B']+26
    # print(data['time_diff'].unique(), len(data['time_diff'].unique()), max(data['time_diff'].unique()))
    return data
    


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
    config['score_diff_num'] = 43 + 1
    config['aroundhead_num'] = 2 + 1
    config['backhand_num'] = 2 + 1
    config['landing_height_num'] = 2 + 1
    config['x_distance_num'] = 2 + 1
    config['y_distance_num'] = 3 + 1

    config['var_dim'] = config['area_dim']
    
    train_matches = feature_extraction(train_matches)
    val_matches = feature_extraction(val_matches)
    test_matches = feature_extraction(test_matches)

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