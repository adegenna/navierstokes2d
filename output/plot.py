import numpy as np
import matplotlib.pyplot as plt

t0 = 0
tf = 50

w0 = np.genfromtxt('out_' + str(t0) + '.csv' , delimiter=',')
wf = np.genfromtxt('out_' + str(tf) + '.csv' , delimiter=',')

plt.figure(1); plt.imshow(w0,vmin=-1,vmax=1);
plt.figure(2); plt.imshow(wf,vmin=-1,vmax=1);
plt.figure(3); plt.imshow(np.abs(wf-w0));

plt.show()
