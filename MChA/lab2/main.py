import numpy as np

k = 5
C = np.array([[0.01, 0, -0.02, 0, 0],
              [0.01, 0.01, -0.02, 0, 0],
              [0, 0.01, 0.01, 0, -0.02],
              [0, 0, 0.01, 0.01, 0],
              [0, 0, 0, 0.01, 0.01]])
D = np.array([[1.33, 0.21, 0.17, 0.12, -0.13],
              [-0.13, -1.33, 0.11, 0.17, 0.12],
              [0.12, -0.13, -1.33, 0.11, 0.17],
              [0.17, 0.12, -0.13, -1.33, 0.11],
              [0.11, 0.67, 0.12, -0.13, -1.33]])
A = k * C + D
b = [1.2, 2.2, 4.0, 0.0, -1.2]

# Ax = b --> x = (E - A)x + b
def SystemTransform(A: np.array, b: np.array):
    A = A.copy()
    c = b.copy()
    for i in range(len(A)):
        assert A[i, i] != 0
        c[i] /= A[i, i]
        A[i] /= A[i, i]
    B = np.identity(len(A)) - A
    return B, c


def FindNorm(A: np.array):
    norm = np.linalg.norm(A)
    if norm < 1:
        return norm
    else:
        norm = np.linalg.norm(A, 1)
        if norm < 1:
            return norm
        else:
            norm = np.linalg.norm(A, np.inf)
            if norm < 1:
                return norm
            else:
                return None;


def isDiagonallyDominantMatrix(A: np.array):
    A = A.copy()
    attempt = 0
    while attempt < 2:
        if attempt == 1:
            A = A.copy().transpose()
        attempt += 1
        for i in range(len(A)):
            Sum = 0
            for j in range(len(A)):
                if i != j:
                    Sum += np.fabs(A[i][j])
            if np.fabs(A[i][i]) <= Sum:
                break
            if i + 1 == len(A):
                return 1;
    return None


# JacobiMethod
def JacobiIteration(B: np.array, x: np.array, c: np.array):
    old_x = x.copy()
    new_x = B @ x + c
    dx = max(np.fabs(new_x - old_x))
    return new_x, dx


def JacobiMethod(A: np.array, b: np.array, margin):
    B, c = SystemTransform(A, b)
    x = np.zeros(len(A))
    norm = FindNorm(B)
    if norm is not None:
        eps = (1 - norm) * margin / norm
    else:
        return None
    dx = 1
    while dx > eps:
        x, dx = JacobiIteration(B, x, c)
        print(x)
    return 1


# SeidelMethod
def SeidelIteration(B: np.array, x: np.array, c: np.array):
    old_x = x.copy()
    for i in range(len(B)):
        x[i] = c[i]
        for j in range(len(B)):
            x[i] += B[i, j] * x[j]
    return max(np.fabs(x - old_x))


def SeidelMethod(A: np.array, b: np.array, margin):
    B, c = SystemTransform(A, b)
    x = np.zeros(len(A))
    norm = FindNorm(B)
    if norm is not None:
        eps = (1 - norm) * margin / norm
    else:
        return None
    dx = 1
    while dx > eps:
        dx = SeidelIteration(B, x, c)
        print(x)
    return 1


if __name__ == '__main__':
    print('A:')
    print(A)
    print('b:')
    print(b)
    print('Jacobi method:')
    if JacobiMethod(A, b, 0.0001) is None:
        print('JacobiMethod cannot be used! Matrix norm > 1')
    print('Seidel method:')
    if SeidelMethod(A, b, 0.0001) is None and not isDiagonallyDominantMatrix(A):
        print('SeidelMethod cannot be used!')
    print('Solution via np.linalg.solve():')
    print(np.linalg.solve(A, b))
