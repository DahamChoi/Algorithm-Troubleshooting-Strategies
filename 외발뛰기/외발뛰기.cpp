#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

int maps[101][101], cache[101][101];
int N;

int jump2(int y, int x) {
	if (y >= N || x >= N) {
		return 0;
	}

	if (y == N - 1 && x == N - 1) {
		return 1;
	}

	int& ret = cache[y][x];
	if (ret != -1) {
		return ret;
	}

	int jumpSize = maps[y][x];
	return ret = (
			jump2(y + jumpSize, x) |
			jump2(y, x + jumpSize)
		);
}

int main() {
	ios::sync_with_stdio(false);	cin.tie(NULL);
	
	int T;	cin >> T;
	while (T-- > 0) {
		cin >> N;

		memset(cache, -1, sizeof(int) * 101 * 101);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> maps[i][j];
			}
		}

		cout << (jump2(0, 0) ? "YES" : "NO");
	}

	return 0;
}