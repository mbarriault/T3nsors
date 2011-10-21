import distutils.core as core

core.setup(
	name = 't3py',
	description = 'T3nsors Python Additions',
	author = 'Mike Barriault',
	author_email = 'mikebarriault@me.com',
	packages = ['t3py'],
	scripts = ['bin/t3.3dcart.py', 'bin/t3.surface.py', 'bin/t3.wavecheck.py', 'bin/t3.l2plot.py', 'bin/t3.quadfit.py']
)
