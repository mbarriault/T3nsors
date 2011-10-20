#!python
import t3py
import sys
import numpy
import math

u = t3py.hdf(sys.argv[1])
Bu = t3py.hdf(sys.argv[2])
theta,r = numpy.meshgrid(u.x[1], u.x[0])

dt = numpy.diff([float(t) for t in u.t])[0]
for i in range(1,u.size()-1):
	udd = (u[i-1] - 2*u[i] + u[i+1]) / (dt**2)
	E = (Bu[i].reshape(r.shape) - udd.reshape(r.shape))**2 * r**2 * numpy.sin(theta)
	#print E
	print math.sqrt(numpy.dot(E.flat,E.flat)/E.size), E.size
