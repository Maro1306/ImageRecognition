# coding: utf-8
import numpy as np
import matplotlib.pyplot as plt

def approx_sigmoid(xs):
	y = np.zeros_like(xs)

	for i, x in enumerate(xs[0]):
		if x < -6.0:                     y[0][i] = 0
		elif (-6.0 <= x) and (x < -5.0): y[0][i] = x * 0.004054 + 0.026365
		elif (-5.0 <= x) and (x < -4.0): y[0][i] = x * 0.010866 + 0.059885
		elif (-4.0 <= x) and (x < -3.0): y[0][i] = x * 0.028453 + 0.128898
		elif (-3.0 <= x) and (x < -2.0): y[0][i] = x * 0.070104 + 0.251117
		elif (-2.0 <= x) and (x < -1.0): y[0][i] = x * 0.149146 + 0.406145
		elif (-1.0 <= x) and (x < -0.7): y[0][i] = x * 0.235004 + 0.495043
		elif (-0.7 <= x) and (x < 0.7):  y[0][i] = x * 0.25 + 0.5
		elif (0.7 <= x) and (x < 1.0):   y[0][i] = x * 0.235004 + 0.504957
		elif (1.0 <= x) and (x < 2.0):   y[0][i] = x * 0.149146 + 0.593855
		elif (2.0 <= x) and (x < 3.0):   y[0][i] = x * 0.070104 + 0.748883
		elif (3.0 <= x) and (x < 4.0):   y[0][i] = x * 0.028453 + 0.871102
		elif (4.0 <= x) and (x < 5.0):   y[0][i] = x * 0.010866 + 0.940115
		elif (5.0 <= x) and (x < 6.0):   y[0][i] = x * 0.004054 + 0.973635
		else:                            y[0][i] = 1.0

	return y

x = np.random.rand(1, 100) * 12 - 6
x = np.sort(x, axis=1)
y = approx_sigmoid(x)

# グラフの描画
plt.plot(x[0].tolist(), y[0].tolist())
plt.ylim(0, 1)
plt.show()