import numpy as np
import matplotlib.pyplot as plt

def gaussian2d(xx,yy,x0,y0,sigma):
    return np.exp(-0.5*( (xx-x0)**2 + (yy-y0)**2 )/sigma**2 )

nx = 256
ny = 256

x     = np.arange(nx)
y     = np.arange(ny)
xx,yy = np.meshgrid(x,y)

centers = 20
sigma   = np.random.uniform(nx/30,nx/20,centers)
x0      = np.random.uniform(0,nx,centers)
y0      = np.random.uniform(0,ny,centers)
amplitude = np.random.uniform(-2,2,centers)
zz      = np.zeros([nx,ny])
for i in range(centers):
    zz += amplitude[i] * gaussian2d(xx,yy,x0[i],y0[i],sigma[i])

plt.contourf(xx,yy,zz); plt.colorbar(); plt.show()

np.savetxt('omega' + str(nx) + '_' + str(ny) + '.csv' , zz , delimiter=',')
