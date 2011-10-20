#!python
import t3py
import sys
import numpy

func = sys.argv[1]
i = int(sys.argv[2])

F = t3py.hdf(func)
theta,r = numpy.meshgrid(F.x[1], F.x[0])
x = r * numpy.cos( theta )
y = r * numpy.sin( theta )

out = open(func[0:-4] + ".txt", 'w')
data = zip(r.flat, theta.flat, F[i].flat)
for datum in data:
	out.write(F.t[i] + "\t")
	for c in datum:
		out.write(str(c) + "\t")
	out.write("\n")
out.close()