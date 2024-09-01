import pandas as pd
import math
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import LabelEncoder
from sklearn.preprocessing import PolynomialFeatures
from sklearn.preprocessing import OneHotEncoder


def data_visualization(data, attribute):
    attribute_count = data[attribute].value_counts()

    plt.bar(attribute_count.index, attribute_count.values, width=0.1)
    plt.xlabel(attribute)
    plt.ylabel('Count')
    plt.title('Separation of Data {}'.format(attribute))
    plt.xticks(rotation=45)
    plt.show()
def calculate_angle(player_x, player_y, opponent_x, opponent_y):
    diff_x = opponent_x - player_x
    diff_y = opponent_y - player_x
    rad_angle = math.atan2(diff_y, diff_x)
    degree_angle = math.degrees(rad_angle)
    if degree_angle < 0:
        degree_angle += 360
    return degree_angle
def Feature_preprocessing(File):
    data = pd.read_csv(File)

    # 1.distance
    data['distance'] = ((data['player_location_x']-data['opponent_location_x'])**2 + (data['player_location_y']-data['opponent_location_y'])**2)**0.5

    # 2.time difference
    data['date_time'] = pd.to_datetime(data['time'])
    time_diff = data['date_time'].diff()
    data['time_diff'] = time_diff.dt.total_seconds()

    # 3.shot angle
    data['shot_angle'] = data.apply(lambda row: calculate_angle(row['player_location_x'], row['player_location_y'], row['opponent_location_x'], row['opponent_location_y']), axis=1)



    # 4. difference between player_location_x and opponent location_x (x-axis distance)
    data['location_difference_x'] = abs(data['player_location_x']-data['opponent_location_x'])


    # 5. difference between player_location_y and opponent location_y(y-axis distance)
    data['location_difference_y'] = abs(data['player_location_y'] - data['opponent_location_y'])


    # xx. use one hot encoding on shot type
    #shot_types = data['type']
    #encoder = OneHotEncoder(sparse=False)
    #encoded_feature = encoder.fit_transform(shot_types.values.reshape(-1, 1))
    #encoded = pd.DataFrame(encoded_feature, columns=encoder.categories_[0])
    #data = pd.concat([data, encoded], axis=1)


    # 6. do classification on the distance on x-axis and y-axis
    # for y-axis , dy>400 -> 2(far), 236 < dy < 400 -> 1(not near nor far) , otherwise 0(near). 236 is the distance of double short service line, 400 is the half of the court.
    # for x-axis , dx>38  -> 1 (slanting angle) , otherwise -> 0 ( straight angle)  (38 is the boundary of some ball type appear or not)
    data['far on y-axis distance'] = np.where(data['location_difference_y'] > 400, 2, np.where((236 < data['location_difference_y']) & (data['location_difference_y'] < 400), 1, 0))
    data['far on x-axis distance'] = np.where(data['location_difference_x'] > 38, 1, 0)



    ###### analysis


    '''
    classes = data['aroundhead'].unique()
    data_per_class = [data[data['aroundhead'] == cls]['location_difference_y'] for cls in classes]
    plt.boxplot(data_per_class, labels=classes)
    plt.ylabel('location_difference_y')
    plt.title('Relation between {} and {}'.format('aroundhead', 'location_difference_y'))
    plt.show()
    
    classes = data['aroundhead'].unique()
    data_per_class = [data[data['aroundhead'] == cls]['location_difference_y'] for cls in classes]
    plt.boxplot(data_per_class, labels=classes)
    plt.ylabel('location_difference_y')
    plt.title('Relation between {} and {}'.format('aroundhead', 'location_difference_y'))
    plt.show()
    
    classes = data['backhand'].unique()
    data_per_class = [data[data['backhand'] == cls]['location_difference_y'] for cls in classes]
    plt.boxplot(data_per_class, labels=classes)  
    plt.xlabel('backhand')
    plt.ylabel('location_difference_y')
    plt.title('Relation between {} and {}'.format('backhand', 'location_difference_y'))
    plt.show()
    '''
    #data_visualization(data, 'far on y-axis distance')
    #data_visualization(data, 'far on x-axis distance')
    #print(data['location_difference_x'].max())
    '''
    plt.scatter(data['type'], data['location_difference_x'])
    plt.xlabel('Shot Type')
    plt.ylabel('Location Difference (X)')
    plt.title('Relation between Shot Type and Location Difference (X)')
    plt.xticks(rotation=45)
    plt.show()
    '''

    '''
    plt.scatter(data['type'], data['location_difference_y'])
    plt.xlabel('Shot Type')
    plt.ylabel('Location Difference (y)')
    plt.title('Relation between Shot Type and Location Difference (y)')
    plt.xticks(rotation=45)
    plt.show()
    '''

    '''
    
    grouped_data = data.groupby('type')['far on y-axis distance'].mean().reset_index()
    grouped_data = grouped_data.sort_values('far on y-axis distance', ascending=False)

    plt.figure(figsize=(10, 6))
    plt.bar(grouped_data['type'], grouped_data['far on y-axis distance'])
    plt.xlabel('Shot Type')
    plt.ylabel('Average Far')
    plt.title('Comparison of Shot type and Far')
    plt.xticks(rotation=45)
    plt.show()

    '''






    # test on data
    #print(data)






