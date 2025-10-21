import numpy as np

def softmax(z):
    exp_z = np.exp(z - np.max(z))  # subtract max for numerical stability
    return exp_z / np.sum(exp_z)

# Example
scores = np.array([2.0, 1.0, 1.0,1,1,1,1,1,0.1,0])
print(softmax(scores))


def scale(z):
    z = np.asarray(z, dtype=float)
    total = np.sum(z)
    if np.isclose(total, 0.0):
        return np.zeros_like(z)
    return z / total
scores1 = np.array([0.5,0.3])
print(scale(scores1))