import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.ensemble import AdaBoostClassifier
from sklearn.metrics import accuracy_score, confusion_matrix

class CarClassifier:
    def __init__(self, model_name, train_data, test_data):

        '''
        Convert the 'train_data' and 'test_data' into the format
        that can be used by scikit-learn models, and assign training images
        to self.x_train, training labels to self.y_train, testing images
        to self.x_test, and testing labels to self.y_test.These four 
        attributes will be used in 'train' method and 'eval' method.
        '''

        self.x_train, self.y_train, self.x_test, self.y_test = None, None, None, None

        # Begin your code (Part 2-1)
        # raise NotImplementedError("To be implemented")
        self.x_train = np.array(list(zip(*train_data))[0])
        self.x_train=self.x_train.reshape((600,36*16))
        # print(self.x_train.shape)
        self.y_train = np.array(list(zip(*train_data))[1])

        self.x_test = np.array(list(zip(*test_data))[0])
        self.x_test = self.x_test.reshape((600,36*16))
        self.y_test = np.array(list(zip(*test_data))[1])
        # End your code (Part 2-1)
        
        self.model = self.build_model(model_name)
        
    
    def build_model(self, model_name):
        '''
        According to the 'model_name', you have to build and return the
        correct model.
        '''
        # Begin your code (Part 2-2)
        # raise NotImplementedError("To be implemented")
        if model_name == "RF":
          rf = RandomForestClassifier(n_estimators = 29, random_state= 2)
          return rf
        elif model_name == "KNN":
          knn = KNeighborsClassifier(n_neighbors = 1)
          return knn
        elif model_name == "AB":
          ab = AdaBoostClassifier(n_estimators = 41)
          return ab
        # End your code (Part 2-2)

    def train(self):
        '''
        Fit the model on training data (self.x_train and self.y_train).
        '''
        # Begin your code (Part 2-3)
        # raise NotImplementedError("To be implemented")
        self.model.fit(self.x_train,self.y_train)
          
        # End your code (Part 2-3)
    
    def eval(self):
        y_pred = self.model.predict(self.x_test)
        print(f"Accuracy: {round(accuracy_score(y_pred, self.y_test), 4)}")
        print("Confusion Matrix: ")
        print(confusion_matrix(y_pred, self.y_test))
    
    def classify(self, input):
        return self.model.predict(input)[0]
        

