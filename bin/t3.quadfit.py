#!python
import t3py
import numpy
import math
import sys
import os
from matplotlib import pyplot
from matplotlib import colors

func = sys.argv[1]
val = sys.argv[2]
runs = sys.argv[3:]

Ms = numpy.linspace(0.25, 1., 7)
V = []
for run in runs:
    F = t3py.hdf(os.path.join(run,func))
    v = F.getparam(val, os.path.join(run,"info.txt"))
    Omega = F.getparam("Omega", os.path.join(run,"info.txt"))
    T = 2*math.pi/Omega
    RLC = 1./Omega
    c = T/float(F.t[-1])
    Sr = numpy.zeros(F.x[0].shape)
    for i in xrange( int(F.size()*(1-c)), F.size()):
        Sr += F.shell(i,0)
    Sr /= F.size()*c
    V.append( (v, Sr) )

for M in Ms:
    U = []
    for v in V:
        i = int( M * (v[1].size-1) )
        U.append((v[0], v[1][i]))
    
    u = [x[0] for x in V]
    L = [x[1] for x in V]
    Lfit = t3py.expfit(u, L)
    
    h = (M - Ms[0])/(Ms[-1]-Ms[0]) * 2./3
    c = colors.hsv_to_rgb(numpy.array([[[h,1,1]]]))
    print Lfit
    print L
    
    C = numpy.zeros((len(L),3))
    for i,Cc in enumerate(C):
        C[i] = c[0,0]
    if len(val) == 1:
        valtex = val
    else:
        valtex = "\\" + val
    
    pyplot.xlabel("$" + valtex + "$")
    pyplot.ylabel(func[:-4])
    pyplot.scatter(u, L, color=C)
    pyplot.plot(u, Lfit[0] * v**Lfit[1], color=c[0,0], label=str(M))
pyplot.legend()
pyplot.show()