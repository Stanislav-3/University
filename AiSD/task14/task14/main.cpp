#include <iostream>

int N, M, U, V, L;
long long mod = 1e9 + 7;

long long adjacencyMatrix[101][101] = {{0}};
long long resultMatrix[101][101] = {{0}};

void buildAdjacencyMatrix(int A, int B);
void binPower(long long (*adjacencyMatrix)[101], int L);

int main(int argc, const char * argv[]) {
    std::cin >> N >> M >> U >> V >> L;
    for(int i = 0, A, B; i < M; ++i) {
        std::cin >> A >> B;
        buildAdjacencyMatrix(A, B);
    }
    
    for (int i = 1; i <= N; ++i) {
        resultMatrix[i][i] = 1;
    }
    binPower(adjacencyMatrix, L);
    
    std::cout << resultMatrix[U][V];
    return 0;
}

void buildAdjacencyMatrix(int A, int B) {
    if (A == B) {
        adjacencyMatrix[A][A] += 2;
    } else {
        adjacencyMatrix[A][B] += 1;
        adjacencyMatrix[B][A] += 1;
    }
}

void binPower(long long (*adjacencyMatrix)[101], int L) {
    while(L) {
        if (L % 2 == 0) {
            L /= 2;
            long long tempMatrix[101][101] = {{0}};
            for (int i = 1; i <= N; ++i) {
                for (int j = 1; j <= N; ++j) {
                    for (int k = 1; k <= N; ++k) {
                        tempMatrix[i][j] += (adjacencyMatrix[i][k] * adjacencyMatrix[k][j]) % mod;
                        tempMatrix[i][j] %= mod;
                    }
                }
            }
            for (int i = 1; i <= N; ++i) {
                for (int j = 1; j <= N; ++j) {
                    adjacencyMatrix[i][j] = tempMatrix[i][j];
                }
            }

        } else {
            --L;
            long long tempMatrix[101][101] = {{0}};
            for (int i = 1; i <= N; ++i) {
                for (int j = 1; j <= N; ++j) {
                    for (int k = 1; k <= N; ++k) {
                        tempMatrix[i][j] += (resultMatrix[i][k] * adjacencyMatrix[k][j]) % mod;
                        tempMatrix[i][j] %= mod;
                    }
                }
            }
            for (int i = 1; i <= N; ++i) {
                for (int j = 1; j <= N; ++j) {
                    resultMatrix[i][j] = tempMatrix[i][j];
                }
            }
        }
    }
}
