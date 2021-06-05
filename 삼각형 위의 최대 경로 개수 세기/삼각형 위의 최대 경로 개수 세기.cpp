#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int N, triangle[100][100];
int countCache[100][100], cache2[100][100];

int path2(int y, int x) {
	if (y == N - 1)	return triangle[y][x];
	int& ret = cache2[y][x];
	if (ret != -1)	return ret;
	return ret = max(path2(y + 1, x), path2(y + 1, x + 1)) + triangle[y][x];
}

int count(int y, int x) {
	if (y == N - 1)	return 1;
	int& ret = countCache[y][x];
	if (ret != -1)	return ret;
	ret = 0;
	if (path2(y + 1, x + 1) >= path2(y + 1, x))	ret += count(y + 1, x + 1);
	if (path2(y + 1, x + 1) <= path2(y + 1, x)) ret += count(y + 1, x);
	return ret;
}

int main() {
	int T;	cin >> T;
	while (T--) {
		cin >> N;

		memset(countCache, -1, sizeof(int) * 100 * 100);
		memset(cache2, -1, sizeof(int) * 100 * 100);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j <= i; j++) {
				cin >> triangle[i][j];
			}
		}

		cout << count(0, 0) << '\n';
	}

	return 0;
}