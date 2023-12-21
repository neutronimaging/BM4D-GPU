import numpy as np
import matplotlib.pyplot as plt

import sys
sys.path.append('../../install')

from pybm4d import pybm4d as bm4d

flt = bm4d.BM4D()
data = np.zeros([128,128,128]).astype(np.uint8)
data[32:96,32:96,32:96] = 64
data = data + 64
ndata = (data + np.random.normal(size=data.shape)*20).astype(np.uint8)
d = ndata.copy()

res = flt.run(d,{"sim_th": 0, "hard_th":  1, "window_size": 4, "step_size": 4}) 

print('hepp')

plt.figure(figsize=(10,10))
plt.imshow(d[64,:,:],cmap='gray')
plt.show()
plt.savefig('BM4D_demo.png')