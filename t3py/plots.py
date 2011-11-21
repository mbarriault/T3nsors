import t3py
import numpy
from matplotlib import pyplot
import os

def l2plotrad(func):
    if type(func) == str:
        F = t3py.hdf(func)
    else:
        F = func
    l2f = []
    theta,r = numpy.meshgrid(F.x[1], F.x[0])
    for f in F:
        val = 0
        if f.rank == 0:
            f = f.reshape(r.shape)
        else:
            f = f[0].reshape(r.shape)
        g = f*(r**2)*numpy.sin(theta)
        l2f.append( math.sqrt(numpy.dot(g.flat,g.flat)/g.size) )
    pyplot.plot(F.t, l2f)
    pyplot.show()
    return l2f

def ratios(runs, func, param, dir="."):
    V = []
    files = os.listdir(dir)
    for f in files:
        if runs in f:
            F = t3py.hdf(os.path.join(dir,f,func))
            v = F.getparam(param,os.path.join(dir,f,"info.txt"))
            V.append((v, F))
    V.sort(key=lambda v : float(v[0]))
    V = numpy.array(V)
    print V
    pyplot.xlabel("$r$", size='xx-large')
    pyplot.ylabel("$q$", size='xx-large')
    if len(param) == 1:
        paramtex = param
    else:
        paramtex = "\\" + param
    print paramtex
    print runs + " $" + func[:-4] + " \propto " + paramtex + "^q$"
    pyplot.suptitle(runs + " $" + func[:-4] + " \propto " + paramtex + "^q$", size='xx-large')
    for i in xrange(len(V)-1):
        Q = numpy.log( V[i+1,1].shell(-1,0)/V[i,1].shell(-1,0) ) / numpy.log( V[i+1,0]/V[i,0] )
        print "$" + paramtex + " = " + repr(V[i,0]) + ",~" + repr(V[i+1,0]) + "$"
        pyplot.plot(V[i,1].x[0], Q, label="$" + paramtex + " = " + repr(V[i,0]) + "," + repr(V[i+1,0]) + "$")
    pyplot.legend()
    pyplot.show()
