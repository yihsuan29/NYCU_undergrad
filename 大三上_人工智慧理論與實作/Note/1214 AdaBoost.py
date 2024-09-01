# -*- coding: utf-8 -*-
"""
Created on Wed Nov 23 19:10:10 2022

@author: USER
"""

import numpy as np
import matplotlib.pyplot as plt
import math

npzfile = np.load('CBCL.npz')
trainface = npzfile['arr_0']
trainnonface = npzfile['arr_1']
testface = npzfile['arr_2']
testnonface = npzfile['arr_3']

trpn = trainface.shape[0]
trnn = trainnonface.shape[0]
tepn = testface.shape[0]
tenn = testnonface.shape[0]

face1 = trainnonface[1200,:].reshape((19,19))
plt.imshow(face1,cmap='gray')

ftable = []
for y in range(19):
    for x in range(19):
        for h in range(2,20):
            for w in range(2,20):
                if(y+h*1-1<=18 and x+w*2-1<=18):
                    ftable.append([0,y,x,h,w])
                if(y+h*2-1<=18 and x+w*1-1<=18):
                    ftable.append([1,y,x,h,w])
                if(y+h*1-1<=18 and x+w*3-1<=18):
                    ftable.append([2,y,x,h,w])
                if(y+h*2-1<=18 and x+w*2-1<=18):
                    ftable.append([3,y,x,h,w])
fn = len(ftable)

def fe(sample,ftable,c):
    ftype,y,x,h,w = ftable[c]
    T = np.arange(361).reshape((19,19))
    if ftype==0:
        output1 = np.sum(sample[:,T[y:y+h,x:x+w].flatten()],axis=1)
        output2 = np.sum(sample[:,T[y:y+h,x+w:x+w*2].flatten()],axis=1)
        output = output1-output2
    elif ftype==1:
        output1 = np.sum(sample[:,T[y:y+h,x:x+w].flatten()],axis=1)
        output2 = np.sum(sample[:,T[y+h:y+h*2,x:x+w].flatten()],axis=1)
        output = output2-output1
    elif ftype==2:
        output1 = np.sum(sample[:,T[y:y+h,x:x+w].flatten()],axis=1)
        output2 = np.sum(sample[:,T[y:y+h,x+w:x+w*2].flatten()],axis=1)
        output3 = np.sum(sample[:,T[y:y+h,x+w*2:x+w*3].flatten()],axis=1)
        output = output1+output3-output2
    else:
        output1 = np.sum(sample[:,T[y:y+h,x:x+w].flatten()],axis=1)
        output2 = np.sum(sample[:,T[y:y+h,x+w:x+w*2].flatten()],axis=1)
        output3 = np.sum(sample[:,T[y+h:y+h*2,x:x+w].flatten()],axis=1)
        output4 = np.sum(sample[:,T[y+h:y+h*2,x+w:x+w*2].flatten()],axis=1)
        output = output2+output3-output1-output4
    return output
            
trpf = np.zeros((trpn,fn))
trnf = np.zeros((trnn,fn))
for c in range(fn):
    trpf[:,c] = fe(trainface,ftable,c)
    trnf[:,c] = fe(trainnonface,ftable,c)
   
def WC(pw,nw,pf,nf):
    maxf = max(pf.max(),nf.max())
    minf = min(pf.min(),nf.min())
    theta = (maxf-minf)/10+minf
    polarity = 1
    error = np.sum(pw[pf<theta])+np.sum(nw[nf>=theta])
    if(error>0.5):
        error = 1-error
        polarity = 0
    min_theta,min_error,min_polarity = theta,error,polarity
    for i in range(2,10):
        theta = (maxf-minf)/10*i+minf
        polarity = 1
        error = np.sum(pw[pf<theta])+np.sum(nw[nf>=theta])
        if(error>0.5):
            error = 1-error
            polarity = 0
        if(error<min_error):
            min_theta,min_error,min_polarity = theta,error,polarity
    return min_error,min_theta,min_polarity

pw = np.ones((trpn,1))/trpn/2
nw = np.ones((trnn,1))/trnn/2
SC = []
T = 10
for t in range(T):
    weightsum = np.sum(pw)+np.sum(nw)
    pw = pw/weightsum
    nw = nw/weightsum
    best_error,best_theta,best_polarity = WC(pw,nw,trpf[:,0],trnf[:,0])
    best_feature = 0
    for i in range(1,fn):
        error,theta,polarity = WC(pw,nw,trpf[:,i],trnf[:,i])
        if(error<best_error):
            best_error,best_theta,best_polarity = error,theta,polarity
            best_feature = i
    beta = best_error/(1-best_error)
    alpha = math.log10(1/beta)
    SC.append([best_feature,best_theta,best_polarity,alpha,beta,best_error])
    if best_polarity == 1:
        pw[trpf[:,best_feature]>=best_theta]*=beta
        nw[trnf[:,best_feature]<best_theta]*=beta
    else:
        pw[trpf[:,best_feature]<best_theta]*=beta
        nw[trnf[:,best_feature]>=best_theta]*=beta
print('SC',SC)
            
trps = np.zeros((trpn,1))
trns = np.zeros((trnn,1))
alpha_sum = 0
for t in range(T):
    [feature,theta,polarity,alpha,beta,error]=SC[t]
    if(polarity==1):
        trps[trpf[:,feature]>=theta] += alpha
        trns[trnf[:,feature]>=theta] += alpha
    else:
        trps[trpf[:,feature]<theta] += alpha
        trns[trnf[:,feature]<theta] += alpha
    alpha_sum += alpha
trps = trps/alpha_sum
trns = trns/alpha_sum
print(np.sum(trps>=0.5)/trpn)
print(np.sum(trns>=0.5)/trnn)

TPR = []
FPR = []
for i in range(0,101):
    TPR.append(np.sum(trps>=i/100)/trpn)
    FPR.append(np.sum(trns>=i/100)/trnn)
