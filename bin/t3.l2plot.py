#!python
import t3py
import numpy
import sys
import math
from matplotlib import pyplot

func = sys.argv[1]

F = t3py.hdf(func)
l2f = []
theta,r = numpy.meshgrid(F.x[1],F.x[0])
for f in F:
	val = 0
	f = f.reshape(r.shape)
	g = f*(r**2)*numpy.sin(theta)
	l2f.append( math.sqrt(numpy.dot(g.flat,g.flat)/g.size) )

pyplot.plot(F.t, l2f)
print l2f
pyplot.show()