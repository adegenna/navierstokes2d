import numpy as np
import matplotlib.pyplot as plt

t0 = 0
tf = 5000
nx = 256
ny = 256

x = np.arange(nx)
y = np.arange(ny)
xx,yy = np.meshgrid(x,y)

# w0 = np.genfromtxt('out_' + str(t0) + '.csv' , delimiter=',')
# wf = np.genfromtxt('out_' + str(tf) + '.csv' , delimiter=',')

# plt.figure(1); plt.imshow(w0,vmin=-1,vmax=1);
# plt.figure(2); plt.imshow(wf,vmin=-1,vmax=1);
# plt.figure(3); plt.imshow(np.abs(wf-w0));

# plt.show()

tstep = 100
fig   = plt.figure(10,figsize=(8,8))
ax    = fig.gca()
plt.ion()
for i in range(int(tf/tstep)):
    print(i*tstep)
    w = np.genfromtxt('out_' + str(int(i*tstep)) + '.csv' , delimiter=',')
    ax.cla()
    ax.contourf(xx,yy,w,30,vmin=-.7,vmax=.7);
    plt.pause(0.01)

plt.ioff()
plt.show()
