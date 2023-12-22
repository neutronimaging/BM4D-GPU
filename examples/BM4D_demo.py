import numpy as np
import matplotlib.pyplot as plt

import sys
sys.path.append('../../install')

from pybm4d import pybm4d as bm4d

flt = bm4d.BM4D()
N=64
N2=N//2
N4=N//4
data = np.zeros([N,N,N]).astype(np.uint8)
data[N4:(N2+N4),N4:(N2+N4),N4:(N2+N4)] = 64
data = data + 64
ndata = (data + np.random.normal(size=data.shape)*20).astype(np.uint8)
d = ndata.copy()

res = flt.run(d,{"sim_th": 500, "hard_th":  2.7, "window_size": 5, "step_size": 3}) 

print('hepp')

fig,ax =plt.subplots(1,3,figsize=(15,5))

ax[0].imshow(ndata[ndata.shape[0]//2,:,:],cmap='gray')
ax[1].imshow(d[d.shape[0]//2,:,:],cmap='gray')
ax[2].imshow(ndata[ndata.shape[0]//2,:,:]-d[d.shape[0]//2,:,:],cmap='gray')
plt.show()
plt.savefig('BM4D_demo.png')