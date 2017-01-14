# coding: utf-8
import numpy as np

def sigmoid(x):
    return 1 / (1 + np.exp(-x))    

def approx_sigmoid(x):
    y = np.zeros(x.shape[1])
    
    y[x < -6.0] = 0
    y = x[(-6.0 <= x) & (x < -5.0)] * 0.004054 + 0.026365
    y = x[(-5.0 <= x) & (x < -4.0)] * 0.010866 + 0.059885
    y = x[(-4.0 <= x) & (x < -3.0)] * 0.028453 + 0.128898
    y = x[(-3.0 <= x) & (x < -2.0)] * 0.070104 + 0.251117
    y = x[(-2.0 <= x) & (x < -1.0)] * 0.149146 + 0.406145
    y = x[(-1.0 <= x) & (x < -0.7)] * 0.235004 + 0.495043
    y = x[(-0.7 <= x) & (x < 0.7)]  * 0.25 + 0.5
    y = x[(0.7 <= x) & (x < 1.0)] * 0.235004 * x + 0.504957
    y = x[(1.0 <= x) & (x < 2.0)] * 0.149146 * x + 0.593855
    y = x[(2.0 <= x) & (x < 3.0)] * 0.070104 * x + 0.748883
    y = x[(3.0 <= x) & (x < 4.0)] * 0.028453 * x + 0.871102
    y = x[(4.0 <= x) & (x < 5.0)] * 0.010866 * x + 0.940115
    y = x[(5.0 <= x) & (x < 6.0)] * 0.004054 * x + 0.973635
    y[6.0 <= x] = 1

def sigmoid_grad(x):
    return (1.0 - sigmoid(x)) * sigmoid(x)
    
def softmax(x):
    if x.ndim == 2:
        x = x.T
        x = x - np.max(x, axis=0)
        y = np.exp(x) / np.sum(np.exp(x), axis=0)
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
