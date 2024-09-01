# -*- coding: utf-8 -*-
"""
Created on Wed Nov  9 19:19:53 2022

@author: USER
"""

import numpy as np
from PIL import Image
from scipy import signal

img = Image.open('photo.jpg')
(w,h)=img.size

I = np.asarray(img).copy()
R = I[:,:,0].astype('float')
G = I[:,:,1].astype('float')
B = I[:,:,2].astype('float')
data = ((R+G+B)/3).astype('uint8')
Sx = np.array([[-1,0,1],[-2,0,2],[-1,0,1]])
Sy = np.array([[-1,-2,-1],[0,0,0],[1,2,1]])
Ix = signal.convolve2d(data,Sx,boundary='symm',mode='same')
Iy = signal.convolve2d(data,Sy,boundary='symm',mode='same')
data2 = (Ix**2)+(Iy**2)
data2_1D = np.sort(data2.reshape((-1,1))[:,0])
threshold = data2_1D[int(len(data2_1D)*0.9)]
data3 = np.zeros((h,w)).astype('uint8')
data3[data2<threshold]=255
img2 = Image.fromarray(data3)
img2.show()







