#include <iostream>
#include <vector>

std::vector<int> neighbors[10000];
bool used[10000] = {0};

void DFS(int vertexNum);

int main(int argc, const char * argv[]) {
    unsigned int N, M;
    int ans;
    std::cin >> N >> M;
    ans = M - (N - 1);
    if(ans < 0) {
        std::cout << -1;
        return 0;
    }
    //add nodes
    for(int i = 0, num1, num2; i < M; i++) {
        std::cin >> num1 >> num2;
        neighbors[num1 - 1].push_back(num2);
        neighbors[num2 - 1].push_back(num1);
    }
    DFS(0);
    for (int i = 0; i < N; ++i) {
        if (!used[i]) {
            ans = -1;
            break;
        }
    }
    if (ans < 0) ans = -1;
    std::cout << ans;
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
