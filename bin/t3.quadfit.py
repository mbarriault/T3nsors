#!python
import t3py
import numpy
import sys
import os
from matplotlib import pyplot

func = sys.argv[1]
val = sys.argv[2]
runs = sys.argv[3:]

V = []
for run in runs:
	F = t3py.hdf(os.path.join(run,func))
	v = F.getparam(val,os.path.join(run,"info.txt"))
	S = F.shell(-1)
	R = F.x[0][0]
	n = F.x[0][-1]*v
	m = 0.9*n
	i = int( (m - R*v)/(n-R*v) * (len(F.x[0]) - 1) )
	V.append( (v, S[i]) )

print V
pyplot.xlabel(val)
pyplot.ylabel(func[:-4])
pyplot.plot([x[0] for x in V], [x[1] for x in V])
pyplot.show()