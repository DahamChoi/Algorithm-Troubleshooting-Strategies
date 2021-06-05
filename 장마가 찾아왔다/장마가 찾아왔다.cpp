#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<double>> cache;

// 달팽이가 days일 동안 climbed미터를 기어올라 왔다고 할때
// m일 전까지 n미터를 기어올라갈 수 있는 경우의 수
double climb(int days, int climbed) {
	if (days == M)	return climbed >= N ? 1.0 : 0.0;

	double& ret = cache[days][climbed];
	if (ret != -1)	return ret;
	return ret = 
		climb(days + 1, climbed + 1) * 0.25 +
		climb(days + 1, climbed + 2) * 0.75;
}

int main() {
	cout.precision(10);

	int T;	cin >> T;
	while (T--) {
		cin >> N >> M;
		cache.assign(N, vector<double>(2 * N + 1, -1));

		cout << climb(0, 0) << '\n';
	}

	return 0;
}