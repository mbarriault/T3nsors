#!python
import t3py
import numpy
import sys
import os
from matplotlib import pyplot
from matplotlib import colors

func = sys.argv[1]
val = sys.argv[2]
runs = sys.argv[3:]

Ms = numpy.linspace(0.8, 1., 3)
for M in Ms:
	V = []
	for run in runs:
		F = t3py.hdf(os.path.join(run,func))
		v = F.getparam(val,os.path.join(run,"info.txt"))
		S = F.shell(-1)
		R = F.x[0][0]
		n = F.x[0][-1]*v
		m = M*n
		i = int( (m - R*v)/(n-R*v) * (len(F.x[0]) - 1) )
		V.append( (v, S[i]) )
	
	v = [x[0] for x in V]
	L = [x[1] for x in V]
	Lfit = numpy.polyfit(v, L, 4)
	
	h = (M - Ms[0])/(Ms[-1]-Ms[0]) * 2./3
	c = colors.hsv_to_rgb(numpy.array([[[h,1,1]]]))
	print Lfit
	
	C = numpy.zeros((len(L),3))
	for i,Cc in enumerate(C):
		C[i] = c[0,0]
	
	pyplot.xlabel(val)
	pyplot.ylabel(func[:-4])
	pyplot.scatter(v, L, color=C)
	pyplot.plot(v, numpy.poly1d(Lfit)(v), color=c[0,0], label=str(M))
pyplot.legend()
pyplot.show()