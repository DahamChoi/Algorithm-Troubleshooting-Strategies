#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int,int>> items;
vector<vector<int>> memory;
int N, M;

int pack(int capacity, int item) {
    if (item == items.size())   return 0;
    int& ref = memory[capacity][item];
    if (ref != -1)   return ref;
    ref = pack(capacity, item + 1);
    if (capacity >= items[item].first) {
        ref = max(ref, pack(capacity - items[item].first, item + 1) + items[item].second);
    }

    return ref;
}

int main() {
    ios::sync_with_stdio(false);	cin.tie(NULL);
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        int V, C, K;    cin >> V >> C >> K;
        for (int j = K; j > 0; j >>= 1) {
            int num = j - (j >> 1);
            items.push_back({ V * num, C * num });
        }
    }

    memory.assign(M + 1, vector<int>(items.size(), -1));
    cout << pack(M, 0);

    return 0;
}