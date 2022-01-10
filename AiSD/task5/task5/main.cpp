#include <iostream>
#include <vector>
#include <set>

long distance[100001];
unsigned long N, M, startV, endV;

std::vector<std::pair<long, long>> neighbors[100001];
std::set<std::pair<long, long>> mySet;

void dijkstra() {
    long curVer;
    distance[startV] = 0;
    mySet.insert(std::pair<long, long>(0, startV));
    
    while(!mySet.empty()) {
        std::pair<long, long> temp = *(mySet.begin());
        mySet.erase(mySet.begin());
        
        curVer = temp.second;
        if (curVer == endV) return;
        
        for (long i = 0, s = (int)neighbors[curVer].size(), neighbor, w; i < s; ++i) {
            neighbor = neighbors[curVer][i].first;
            w = neighbors[curVer][i].second;
            
            if (distance[curVer] + w < distance[neighbor]) {
                distance[neighbor] = distance[curVer] + w;
                mySet.insert(std::pair<long, long>(distance[neighbor], neighbor));
            }
        }
        
    }
}

int main(int argc, const char * argv[]) {
    for(long i = 0; i < 100001; ++i) {
        distance[i] = 1e18;
    }
    //N -- vertexes Num | M -- edges Num
    std::cin >> N >> M;
    for (long i = 0, num1, num2, c; i < M; ++i) {
        std::cin >> num1 >> num2 >> c;
        neighbors[num1].push_back(std::pair<int, int>(num2, c));
        neighbors[num2].push_back(std::pair<int, int>(num1, c));
    }
    std::cin >> startV >> endV;
    dijkstra();
    
    std::cout << distance[endV];
    return 0;
}
