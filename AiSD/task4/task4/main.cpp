#include <iostream>
#include <queue>

std::queue<std::pair<unsigned int, unsigned int>> q;
std::pair<unsigned int, unsigned int> p;
bool used[102][102] = {0};
unsigned int n, m, i, j, xCur, yCur;
int count[102][102] = {0};
int prevCount = 0;

int BFS(int x, int y);
void addNeighborsToQueue(unsigned int xCur, unsigned int yCur);
bool inFrame(int x, int y);

int main(int argc, const char * argv[]) {
    std::cin >> n >> m >> i >> j;
    BFS(1, 1) < 0? std::cout << "NEVAR" : std::cout << prevCount;
    return 0;
}

int BFS(int x, int y) {
    used[x][y] = true;
    count[x][y] = 0;
    q.push(std::pair<int, int> (x, y));
    while(!q.empty()) {
        p = q.front();
        q.pop();
        xCur = p.first;
        yCur = p.second;
        prevCount = count[xCur][yCur];
//        std::cout << "(" << xCur << " | " << yCur << ")\n";
        if (xCur == i && yCur == j) return prevCount;
        addNeighborsToQueue(xCur, yCur);
//        std::cout << std::endl;
    }
    return -1;
}

void addNeighborsToQueue(unsigned int xCur, unsigned int yCur) {
    unsigned int nX = xCur - 2, nY = yCur + 1;
    if (inFrame(nX, nY) && !used[nX][nY]) {
        q.push(std::pair<int, int> (nX, nY));
        used[nX][nY] = true;
        count[nX][nY] += prevCount + 1;
    }
    nY = yCur - 1;
    if (inFrame(nX, nY) && !used[nX][nY]) {
        q.push(std::pair<int, int> (nX, nY));
        used[nX][nY] = true;
        count[nX][nY] += prevCount + 1;
    }
    
    nX = xCur - 1; nY = yCur + 2;
    if (inFrame(nX, nY) && !used[nX][nY]) {
        q.push(std::pair<int, int> (nX, nY));
        used[nX][nY] = true;
        count[nX][nY] += prevCount + 1;
    }
    nY = yCur - 2;
    if (inFrame(nX, nY) && !used[nX][nY]) {
        q.push(std::pair<int, int> (nX, nY));
        used[nX][nY] = true;
        count[nX][nY] += prevCount + 1;
    }
    
    nX = xCur + 1; nY = yCur + 2;
    if (inFrame(nX, nY) && !used[nX][nY]) {
        q.push(std::pair<int, int> (nX, nY));
        used[nX][nY] = true;
        count[nX][nY] += prevCount + 1;
    }
    nY = yCur - 2;
    if (inFrame(nX, nY) && !used[nX][nY]) {
        q.push(std::pair<int, int> (nX, nY));
        used[nX][nY] = true;
        count[nX][nY] += prevCount + 1;
    }
    
    nX = xCur + 2; nY = yCur + 1;
    if (inFrame(nX, nY) && !used[nX][nY]) {
        q.push(std::pair<int, int> (nX, nY));
        used[nX][nY] = true;
        count[nX][nY] += prevCount + 1;
    }
    nY = yCur - 1;
    if (inFrame(nX, nY) && !used[nX][nY]) {
        q.push(std::pair<int, int> (nX, nY));
        used[nX][nY] = true;
        count[nX][nY] += prevCount + 1;
    }
}

bool inFrame(int x, int y) {
    if (x >= 1 && x <= n && y >= 1 && y <= m) {
        return true;
    }
    else {
        return false;
    }
}

//void BFS(int x, int y, int& count) {
////    q.push(std::pair<int, int> (x, y));
//    p = q.front();
//    q.pop();
//    xCur = p.first;
//    yCur = p.second;
//    if (xCur == i && yCur == j) {
//        return;
//    }
//    else {
//        count += 1;
//        addNeighborsToQueue(xCur, yCur);
//    }
//
//    if (q.empty()) {
//        count = -1;
//        return;
//    }
//    return BFS(xCur, yCur, count);
//}
