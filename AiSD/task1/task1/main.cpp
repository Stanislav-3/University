#include <iostream>
#include <vector>

int N, M;
std::vector<int> neighbors[100001];
bool used[10000] = {0};

void DFS(int vertexNum);

int main(int argc, const char * argv[]) {
    std::cin >> N >> M;
    for(int i = 0, num1, num2; i < M; i++) {
        std::cin >> num1 >> num2;
        neighbors[num1 - 1].push_back(num2);
        neighbors[num2 - 1].push_back(num1);
    }
    int c = -1;
    for(int i = 0; i < N; i++) {
        if(!used[i]) {
            DFS(i);
            c++;
        }
    }
    std::cout << c;
    return 0;
}

void DFS(int vertexNum) {
    used[vertexNum] = true;
    for(int i = 0; i < neighbors[vertexNum].size(); i++) {
        int neighbor = neighbors[vertexNum][i] - 1;
        if (!used[neighbor]) {
            DFS(neighbor);
        }
    }
}
