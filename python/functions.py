# coding: utf-8
import numpy as np

def sigmoid(x):
    return 1 / (1 + np.exp(-x))    

def approx_sigmoid(xs):
    y = np.zeros_like(xs)

    for i, x in enumerate(xs):
        for j, x in enumerate(xs[i]):
            if x < -6.0:                     y[i][j] = 0
            elif (-6.0 <= x) and (x < -5.0): y[i][j] = x * 0.004054 + 0.026365
            elif (-5.0 <= x) and (x < -4.0): y[i][j] = x * 0.010866 + 0.059885
            elif (-4.0 <= x) and (x < -3.0): y[i][j] = x * 0.028453 + 0.128898
            elif (-3.0 <= x) and (x < -2.0): y[i][j] = x * 0.070104 + 0.251117
            elif (-2.0 <= x) and (x < -1.0): y[i][j] = x * 0.149146 + 0.406145
            elif (-1.0 <= x) and (x < -0.7): y[i][j] = x * 0.235004 + 0.495043
            elif (-0.7 <= x) and (x < 0.7):  y[i][j] = x * 0.25 + 0.5
            elif (0.7 <= x) and (x < 1.0):   y[i][j] = x * 0.235004 + 0.504957
            elif (1.0 <= x) and (x < 2.0):   y[i][j] = x * 0.149146 + 0.593855
            elif (2.0 <= x) and (x < 3.0):   y[i][j] = x * 0.070104 + 0.748883
            elif (3.0 <= x) and (x < 4.0):   y[i][j] = x * 0.028453 + 0.871102
            elif (4.0 <= x) and (x < 5.0):   y[i][j] = x * 0.010866 + 0.940115
            elif (5.0 <= x) and (x < 6.0):   y[i][j] = x * 0.004054 + 0.973635
            else:                            y[i][j] = 1.0

    return y

def sigmoid_grad(x):
    return (1.0 - sigmoid(x)) * sigmoid(x)

def approx_sigmoid_grad(xs):
    y = np.zeros_like(xs)

    for i, x in enumerate(xs[0]):
        if (-6.0 <= x) and (x < -5.0): y[0][i] = 0.004054
        elif (-5.0 <= x) and (x < -4.0): y[0][i] = 0.010866
        elif (-4.0 <= x) and (x < -3.0): y[0][i] = 0.028453
        elif (-3.0 <= x) and (x < -2.0): y[0][i] = 0.070104
        elif (-2.0 <= x) and (x < -1.0): y[0][i] = 0.149146
        elif (-1.0 <= x) and (x < -0.7): y[0][i] = 0.235004
        elif (-0.7 <= x) and (x < 0.7):  y[0][i] = 0.25
        elif (0.7 <= x) and (x < 1.0):   y[0][i] = 0.235004
        elif (1.0 <= x) and (x < 2.0):   y[0][i] = 0.149146
        elif (2.0 <= x) and (x < 3.0):   y[0][i] = 0.070104
        elif (3.0 <= x) and (x < 4.0):   y[0][i] = 0.028453
        elif (4.0 <= x) and (x < 5.0):   y[0][i] = 0.010866
        elif (5.0 <= x) and (x < 6.0):   y[0][i] = 0.004054
        else:                            y[0][i] = 0

    return y

def softmax(x):
    if x.ndim == 2:
        x = x.T
        x = x - np.max(x, axis=0)
        y = np.exp(x) / np.sum(np.exp(x), axis=0)
        print(1.0/np.sum(np.exp(x), axis=0))

        return y.T 

    x = x - np.max(x) # オーバーフロー対策
    return np.exp(x) / np.sum(np.exp(x))

def mean_squared_error(y, t):
    return 0.5 * np.sum((y-t)**2)

def cross_entropy_error(y, t):
    if y.ndim == 1:
        t = t.reshape(1, t.size)
        y = y.reshape(1, y.size)
        
    # 教師データがone-hot-vectorの場合、正解ラベルのインデックスに変換
    if t.size == y.size:
        t = t.argmax(axis=1)
             
    batch_size = y.shape[0]
    return -np.sum(np.log(y[np.arange(batch_size), t])) / batch_size

def softmax_loss(X, t):
    y = softmax(X)
    return cross_entropy_error(y, t)
