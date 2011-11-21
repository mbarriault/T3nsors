#!python
import t3py
from t3py import plots
import sys

runs = sys.argv[1]
func = sys.argv[2]
param = sys.argv[3]

plots.ratios(runs, func, param)
