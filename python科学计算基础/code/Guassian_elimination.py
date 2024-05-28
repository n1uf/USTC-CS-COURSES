import numpy as np

def Gaussian_elimination_v1(A):
    m, n = np.shape(A)
    for j in range(n - 1):
        for i in range(j + 1, m):
            A[i, :] -= (A[i, j] / A[j, j]) * A[j, :]
    return A

A = np.array([[2.0,3,5,7], [11,13,17,19], [23,29,31,37]])
print(Gaussian_elimination_v1(A))

B = np.array([[2.0,3,5,7], [12,18,17,19], [23,29,31,37]])
print(Gaussian_elimination_v1(B))