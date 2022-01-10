import numpy as np

variant = 6
eps = 1e-4

def input():
    C = np.array([
        [0.2, 0.0, 0.2, 0.0, 0.0],
        [0.0, 0.2, 0.0, 0.2, 0.0],
        [0.2, 0.0, 0.2, 0.0, 0.2],
        [0.0, 0.2, 0.0, 0.2, 0.0],
        [0.0, 0.0, 0.2, 0.0, 0.2]
        ])
    D = np.array([
        [ 2.33,  0.81,  0.67,  0.92, -0.53],
        [ 0.81,  2.33,  0.81,  0.67,  0.92],
        [ 0.67,  0.81,  2.33,  0.81,  0.92],
        [ 0.92,  0.67,  0.81,  2.33, -0.53],
        [-0.53,  0.92,  0.92, -0.53,  2.33]
        ])
    A = variant * C + D
    return A

def check_symmetry(A):
    if not np.array_equal(A.T, A):
        raise Exception('Матрица должна быть симметричной!')

def find_eigenvectors():
    A = input()
    try:
        check_symmetry(A.copy())
    except:
        raise

    ansV = np.eye(len(A))
    count = 0
    while True:
        count += 1
        maxelem = (0, 1)
        for i in range(len(A)):
            for j in range(i + 1, len(A)):
                if (abs(A[i][j]) > abs(A[maxelem])):
                    maxelem = (i, j)
        (i, j) = maxelem
        if (A[i][i] == A[j][j]):
            p = np.pi / 4
        else:
            p = 2 * A[i][j] / (A[i][i] - A[j][j])

        c = np.cos(1/2 * np.arctan(p))
        s = np.sin(1/2 * np.arctan(p))
        V = np.eye(len(A))
        V[i][i] = c
        V[i][j] = -s
        V[j][i] = s
        V[j][j] = c
        A = V.T @ A @ V
        ansV = ansV @ V
        if (np.sqrt(((A ** 2).sum() - (np.diag(A) ** 2).sum())  / (len(A) ** 2 / 2)) < eps):
            ansW = np.diag(A)
            break

    np.set_printoptions(suppress = True, precision = int(abs(np.log10(eps))), floatmode = "fixed")
    return (ansW, ansV, count)

def print_vectors(matrix):
    for i in range(len(matrix)):
        print(f'υ{i + 1} = {matrix[:, i]}')

if __name__ ==  '__main__':
    A = input()
    print("A: \n", A, end="\n\n")
    try:
        (W, V, count) = find_eigenvectors()
    except Exception as e:
        print(e)
        exit(0)
    print("Вектор собственных значений:\n"
          " λ =", W)
    print("Cобственные векторы: ")
    print_vectors(V)
    print("Количество итераций: ", count, end="\n\n")

    print("Проверка с помощью встроенной функции:")
    (W, V) = np.linalg.eig(A)
    print("Вектор собственных значений:\n"
          " λ =", W)
    print("Cобственные векторы: ")
    print_vectors(V)


