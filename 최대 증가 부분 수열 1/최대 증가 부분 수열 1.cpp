#include <iostream>
#include <vector>

using namespace std;

vector<int> cache, numberic;

int lis(int start) {
	int& ret = cache[start + 1];
	if (ret != -1)	return ret;
	ret = 1;
	for (int next = start + 1; next < numberic.size(); next++) {
		if (start == -1 || numberic[start] < numberic[next]) {
			ret = max(ret, lis(next) + 1);
		}
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);	cin.tie(NULL);
	int N;	cin >> N;
	cache.assign(N + 1, -1);
	numberic.assign(N, 0);
	for (int i = 0; i < N; i++) {
		cin >> numberic[i];
	}

	cout << (lis(-1) - 1);

	return 0;
}