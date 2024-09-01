import os
import cv2
import numpy as np

def load_images(data_path):
    """
    Load all Images in the folder and transfer a list of tuples. 
    The first element is the numpy array of shape (m, n) representing the image.
    (remember to resize and convert the parking space images to 36 x 16 grayscale images.) 
    The second element is its classification (1 or 0)
      Parameters:
        dataPath: The folder path.
      Returns:
        dataset: The list of tuples.
    """
    # Begin your code (Part 1)
    dataset=[]
    for f in range(2):
      folder_path = os.path.join(data_path, 'car')if f == 0 else os.path.join(data_path, 'non-car')
      flag = (f+1)%2
      for filename in os.listdir(folder_path):
        img=cv2.imread(os.path.join(folder_path, filename))
        if img is not None:
          img = cv2.resize(img, (36,16))
          gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
          np_img = np.array(gray_img)
          image = tuple((np_img, flag))
          dataset.append(image)
    # raise NotImplementedError("To be implemented")
    # End your code (Part 1)
    return dataset
