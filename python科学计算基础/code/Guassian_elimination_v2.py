import numpy as np

def Gaussian_elimination_v2(A, tol = 1e-10):
    m, n = np.shape(A)
    i = 0
    for j in range(n):
        p = np.argmax(abs(A[i:m, j]))
        if p > 0:                       # swap rows
            A[[i, p + i]] = A[[p + i, i]]
        if abs(A[i, j]) > tol:          # j is a pivot column
            for r in range(i + 1, m):
                A[r, j:] -= (A[r, j] / A[i, j]) * A[i, j:]
            i += 1
            if i >= m: break
    return A, i

A = np.array([[2.0,3,5,7], [11,13,17,19], [23,29,31,37]])
print(Gaussian_elimination_v2(A))

B = np.array([[2.0,3,5,7], [12,18,17,19], [23,29,31,37]])
print(Gaussian_elimination_v2(B))