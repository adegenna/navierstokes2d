import numpy as np
import matplotlib.pyplot as plt
from matplotlib import animation

t0 = 0
tf = 100000
nx = 256
ny = 256

x = np.arange(nx)
y = np.arange(ny)
xx,yy = np.meshgrid(x,y)

tstep = 5000
fig   = plt.figure(10,figsize=(8,8))
ax    = fig.gca()

# animation function.  This is called sequentially
def animate(i):
    print(i*tstep)
    w = np.genfromtxt('../output/out_' + str(int(i*tstep)) + '.csv' , delimiter=',')
    ax.cla()
    contour = ax.contourf(xx,yy,w,30,vmin=-0.7,vmax=0.7)
    return contour

anim = animation.FuncAnimation(fig, animate,
                               frames=int(tf/tstep)+1, interval=20)
#anim.save('ns2d.mp4', fps=30, extra_args=['-vcodec', 'libx264'])
plt.show()


# plt.ion()
# for i in range(int(tf/tstep)):
#     print(i*tstep)
#     w = np.genfromtxt('out_' + str(int(i*tstep)) + '.csv' , delimiter=',')
#     ax.cla()
#     ax.contourf(xx,yy,w,30,vmin=-.7,vmax=.7);
#     plt.pause(0.01)

# plt.ioff()
# plt.show()
