#include <iostream>
#include <vector>

using namespace std;

void generate(int n, int m, string s) {
	// 기저 사례 : n = m = 0
	if (n == 0 && m == 0) {
		return;
	}

	if (n > 0)	generate(n - 1, m, s + "-");
	if (m > 0)	generate(n, m - 1, s + "o");
}

int skip;
void generate2(int n, int m, string s) {
	// 기저 사례 : skip < 0
	if (skip < 0)	return;
	// 기저 사례 : n = m = 0
	if (n == 0 && m == 0) {
		--skip;
		return;
	}

	if (n > 0)	generate2(n - 1, m, s + "-");
	if (m > 0)	generate2(n, m - 1, s + "o");
}

// K의 최댓값 + 100, 오버플로를 막기 위해 이보다 큰 값은 구하지 않는다.
const int M = 1000000000 + 100;
int bino[201][201];
void calcBino() {
	memset(bino, 0, sizeof(bino));
	for (int i = 0; i <= 200; i++) {
		bino[i][0] = bino[i][i] = 1;
		for (int j = 1; j < i; j++) {
			bino[i][j] = min(M, bino[i - 1][j - 1] + bino[i - 1][j]);
		}
	}
}

void generate3(int n, int m, string s) {
	if (skip < 0)	return;
	if (n == 0 && m == 0) {
		--skip;
		return;
	}

	if (bino[n + m][n] <= skip) {
		skip -= bino[n + m][n];
		return;
	}

	if (n > 0)	generate3(n - 1, m, s + "-");
	if (m > 0)	generate3(n, m - 1, s + "o");
}

string kth(int n, int m, int skip) {
	if (n == 0)	return string(m, 'o');
	if (skip < bino[n + m - 1][n - 1]) {
		return "-" + kth(n - 1, m, skip);
	}
	return "o" + kth(n, m - 1, skip - bino[n + m - 1][n - 1]);
}

int main() {
	ios::sync_with_stdio(false);	cin.tie(NULL);
	int T;	cin >> T;
	while (T--) {
		int N, M, K;	cin >> N >> M >> K;
	}

	return 0;
}