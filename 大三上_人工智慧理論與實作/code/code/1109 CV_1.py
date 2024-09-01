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
img = img.resize((w//10,h//10))
I = np.asarray(img).copy()
R = I[:,:,0].astype('float')
G = I[:,:,1].astype('float')
B = I[:,:,2].astype('float')
data = ((R+G+B)/3).astype('uint8')
mask = np.array([[1/9,1/9,1/9],[1/9,1/9,1/9],[1/9,1/9,1/9]])
mask2 = np.array([[0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1]])
data2 = signal.convolve2d(data,mask2,boundary='symm',mode='same')
img2 = Image.fromarray(data2)
img2.show()







