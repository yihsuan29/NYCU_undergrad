import numpy as np
import random
import matplotlib.pyplot as plt

npzfile = np.load('CBCL.npz')
trainface = npzfile['arr_0']
trainnonface = npzfile['arr_1']
testface = npzfile['arr_2']
testnonface = npzfile['arr_3']

trpn = trainface.shape[0]
trnn = trainnonface.shape[0]
tepn = testface.shape[0]
tenn = testnonface.shape[0]

def BPNNtrain(pf,nf,hn,lr,epoch):
    pn = pf.shape[0]
    nn = nf.shape[0]
    fn = pf.shape[1]
    feature = np.append(pf,nf,axis=0)
    target = np.append(np.ones((pn,1)),np.zeros((nn,1)),axis=0)
    
    WI = np.random.normal(0,1,(fn+1,hn))
    WO = np.random.normal(0,1,(hn+1,1))
    
    for t in range(epoch):
        print(t)
        s = random.sample(range(pn+nn),pn+nn)
        for i in range(pn+nn):
            ins = np.append(feature[s[i],:],1)
            ho = ins.dot(WI)
            ho = 1/(1+np.exp(-ho))
            hs = np.append(ho,1)
            out = hs.dot(WO)
            out = 1/(1+np.exp(-out))
            dk = out*(1-out)*(target[s[i]]-out)
            dh = ho*(1-ho)*WO[:hn,0]*dk
            WO[:,0] += lr*dk*hs
            for j in range(hn):
                WI[:,j] += lr*dh[j]*ins
    model = dict()
    model['WI'] = WI
    model['WO'] = WO
    return model

def BPNNtest(feature,network):
    sn = feature.shape[0]
    WI = network['WI']
    WO = network['WO']
    hn = WI.shape[1]
    out = np.zeros((sn,1))
    for i in range(sn):
        ins = np.append(feature[i,:],1)
        ho = ins.dot(WI)
        ho = 1/(1+np.exp(-ho))
        hs = np.append(ho,1)
        out[i] = hs.dot(WO)
        out[i] = 1/(1+np.exp(-out[i]))
    return out

network = BPNNtrain(trainface/255,trainnonface/255,100,0.01,10)
pscore = BPNNtest(trainface/255,network)
nscore = BPNNtest(trainnonface/255,network)

pscore = BPNNtest(testface/255,network)
nscore = BPNNtest(testnonface/255,network)    
    
face1 = testnonface[14857,:].reshape((19,19))
plt.imshow(face1,cmap='gray')   
    
    