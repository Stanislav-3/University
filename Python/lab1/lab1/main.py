import numpy as np

def func(matrix_size):
    matrix = np.random.randint(0, 10, size=(matrix_size, matrix_size))
    return matrix, matrix.transpose()

if __name__ == '__main__':
    matrix, transposed_matrix = func(6)
    print("Random matrix:\n", matrix)
    print("Transposed random matrix:\n", transposed_matrix)