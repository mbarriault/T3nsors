import h5py
import numpy
import math

class hdf:
    def __init__(self, file):
        self.file = file
        self.f = h5py.File(file, 'r')
        self.t = sorted(self.f['data'].keys(), key=lambda x : float(x))
        self.cnt = 0
        F = self.f['data'][self.t[0]]
        if type(F) is h5py._hl.dataset.Dataset:
            self.rank = 0
            self.shape = F.shape
        elif type(F) is h5py._hl.group.Group:
            self.rank = len(F.keys())
            self.shape = F['0'].shape
        self.x = []
        X = sorted(self.f['coords'].items())
        for i,(c,x) in enumerate(X):
            ar = numpy.arange(x[0], x[1]+x[2]/2, x[2])
            if len(ar) > self.shape[i]:
                ar = ar[:-1]
            self.x.append(ar)
    def __del__(self):
        self.f.close()
    def __getitem__(self, index):
        key = self.t[index]
        F = self.f['data'][key]
        if self.rank == 0:
            f = numpy.array(F)
            f = f.reshape(f.shape, order='F')
        else:
            f = []
            for c in self.f['data'][key]:
                Fc = numpy.array(F[c])
                Fc = Fc.reshape(Fc.shape, order='F')
                f.append(Fc)
        return f
    def size(self):
        return len(self.t)
    def __iter__(self):
        return self
    def next(self):
        try:
            result = self[self.cnt]
            self.cnt += 1
            return result
        except:
            raise StopIteration
    def shell(self,i,c=0):
        if self.rank == 0:
            f = self[i]
        else:
            f = self[i][c]
        shape = f.shape[0:1]
        s = numpy.zeros(shape)
        for j in xrange(f.shape[1]):
            for k in xrange(f.shape[2]):
                s += f[:,j,k] * (self.x[0])**2 * numpy.sin(self.x[1][j])
        s -= 0.5 * ( f[:,0,0] * (self.x[0])**2 * numpy.sin(self.x[1][0]) + f[:,-1,0] * (self.x[0])**2 * numpy.sin(self.x[1][-1]) )
        s *= 2*math.pi * (self.x[1][-1]-self.x[1][0])/self.x[1].size
        return s
    def getparam(self,param,file="info.txt"):
        info = open(file, 'r')
        for line in info.readlines():
            if param in line:
                try:
                    val = float( line.split(' ')[2] )
                    break
                except IndexError:
                    pass
        return val

def expfit(x, y):
    logx = numpy.log(x)
    logy = numpy.log(y)
    logfit = numpy.polyfit(logx, logy, 1)
    b = logfit[0]
    a = numpy.exp(logfit[1])
    r = (y - a*x**b)**2
    return (a, b, numpy.dot(r,r) )

