#!python
import t3py
import sys
import numpy
from matplotlib import pyplot
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D

func = sys.argv[1]
i = int(sys.argv[2])

F = t3py.hdf(func)
theta,r = numpy.meshgrid(F.x[1], F.x[0])
x = r * numpy.cos( theta )
y = r * numpy.sin( theta )

fig = pyplot.figure()
ax = fig.gca(projection='3d')
ax.plot_surface(x, y, F[i].reshape(x.shape), rstride=1, cstride=1, cmap=cm.jet, linewidth=0, antialiased=False)

pyplot.show()
