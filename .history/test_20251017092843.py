import numpy as np

def softmax(z):
    exp_z = np.exp(z - np.max(z))  # subtract max for numerical stability
    return exp_z / np.sum(exp_z)

# Example
scores = np.array([2.0, 1.0, 0.1])
print(softmax(scores))
