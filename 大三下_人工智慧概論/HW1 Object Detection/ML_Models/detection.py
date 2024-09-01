import cv2
import matplotlib.pyplot as plt
import numpy as np
import os

def crop(x1, y1, x2, y2, x3, y3, x4, y4, img) :
    """
    This function ouput the specified area (parking space image) of the input frame according to the input of four xy coordinates.
    
      Parameters:
        (x1, y1, x2, y2, x3, y3, x4, y4, frame)
        
        (x1, y1) is the lower left corner of the specified area
        (x2, y2) is the lower right corner of the specified area
        (x3, y3) is the upper left corner of the specified area
        (x4, y4) is the upper right corner of the specified area
        frame is the frame you want to get it's parking space image
        
      Returns:
        parking_space_image (image size = 360 x 160)
      
      Usage:
        parking_space_image = crop(x1, y1, x2, y2, x3, y3, x4, y4, img)
    """
    left_front = (x1, y1)
    right_front = (x2, y2)
    left_bottom = (x3, y3)
    right_bottom = (x4, y4)
    src_pts = np.array([left_front, right_front, left_bottom, right_bottom]).astype(np.float32)
    dst_pts = np.array([[0, 0], [0, 160], [360, 0], [360, 160]]).astype(np.float32)
    projective_matrix = cv2.getPerspectiveTransform(src_pts, dst_pts)
    croped = cv2.warpPerspective(img, projective_matrix, (360,160))
    return croped


def detect(data_path, clf):
    """
    Please read detectData.txt to understand the format. 
    Use cv2.VideoCapture() to load the video.gif.
    Use crop() to crop each frame (frame size = 1280 x 800) of video to get parking space images. (image size = 360 x 160) 
    Convert each parking space image into 36 x 16 and grayscale.
    Use clf.classify() function to detect car, If the result is True, draw the green box on the image like the example provided on the spec. 
    Then, you have to show the first frame with the bounding boxes in your report.
    Save the predictions as .txt file (ML_Models_pred.txt), the format is the same as Sample.txt.
    
      Parameters:
        dataPath: the path of detectData.txt
      Returns:
        No returns.
    """
    # Begin your code (Part 4)
    # raise NotImplementedError("To be implemented")
    i=0;
    coordinate=[]
    with open(data_path, 'r') as f:
        for line in f:
            if i==0:
                i=1
                continue
            xy=line.split()
            xy = list(map(int, xy))
            coordinate.append(xy)
    
    result = open("data/detect/ML_Models_pred.txt", "a")
    pict=1
    video=cv2.VideoCapture("data/detect/video.gif")
    cars=0
    if video.isOpened:
        while True:
            success,img=video.read()
            if success:
              result.write(str(pict)+"\n")
              for cor in coordinate:
                parking_space_image = crop(cor[0], cor[1], cor[2], cor[3], cor[4], cor[5], cor[6], cor[7], img)
                parking_space_image = cv2.resize(parking_space_image, (36,16))
                gray_img = cv2.cvtColor(parking_space_image, cv2.COLOR_BGR2GRAY)
                np_img = np.array(gray_img).reshape(1,-1)
                is_car= 1 if clf.classify(np_img) else 0
                s=" ".join(str(e) for e in cor)
                s+=" "+str(is_car)
                if is_car == 1:
                  img=cv2.rectangle(img, pt1=(cor[0],cor[1]), pt2=(cor[6],cor[7]), color=(0,255,0), thickness=3)
                  cars+=1
                result.write(s+"\n")
              if pict==1:
                # print(cars)
                cv2.imwrite("data/detect/ML_Models_pred.png",img)
              pict+=1
            else:
              # print("Oh no")
              result.close()
              break

    result.close()
    # End your code (Part 4)
