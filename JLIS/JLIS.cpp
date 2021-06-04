#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int N, M;
vector<int> A, B;
vector<vector<int>> cache;

int jlis(int indexA, int indexB) {
    int& ret = cache[indexA + 1][indexB + 1];
    if (ret != -1)   return ret;

    ret = 2;
    long long a = (indexA == -1 ? -INT_MAX : A[indexA]);
    long long b = (indexB == -1 ? -INT_MAX : B[indexB]);
    long long maxElement = max(a, b);

    for (int nextA = indexA + 1; nextA < N; nextA++) {
        if (maxElement < A[nextA]) {
            ret = max(ret, jlis(nextA, indexB) + 1);
        }
    }

    for (int nextB = indexB + 1; nextB < M; nextB++) {
        if (maxElement < B[nextB]) {
            ret = max(ret, jlis(indexA, nextB) + 1);
        }
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);	cin.tie(NULL);
    int T;  cin >> T;
    while (T--) {
        cin >> N >> M;
        A.assign(N, 0); B.assign(M, 0);
        cache.assign(N + 1, vector<int>(M + 1, -1));

        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }

        for (int i = 0; i < M; i++) {
            cin >> B[i];
        }

        cout << (jlis(-1, -1) - 2) << '\n';
    }

    return 0;
}