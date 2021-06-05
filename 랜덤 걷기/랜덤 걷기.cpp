#include <iostream>
#include <vector>

using namespace std;

vector<vector<double>> dp;
int N;
double L, R, C;

double search(int here, int days, int goal) {
	if (days == N)		return 1.0;

	double& ref = dp[here][days];
	if (ref > -0.5)		return ref;

	ref = 0.0;
	ref += search(here - 1, days + 1, goal) * L;
	ref += search(here, days + 1, goal) * C;
	if (here + 1 <= goal) {
		ref += search(here + 1, days + 1, goal) * R;
	}
	return ref;
}

int main() {
	cout.precision(5);

	int T;	cin >> T;
	while (T--) {
		cin >> N;
		cin >> L >> R;
		C = 1.0 - L - R;

		vector<double> v_sum;
		for (int i = N; i <= N + N; i++) {
			dp.assign(N * 2 + 1, vector<double>(N + 1, -1.0));
			double sum = search(N, 0, i);
			if (sum >= 1.0) {
				for (int k = i; k <= N + N; k++) {
					v_sum.push_back(1.0);
				}
				break;
			}
			else {
				v_sum.push_back(search(N, 0, i));
			}
		}

		double answer = 0.0;
		for (int i = v_sum.size() - 1; i > 0; i--) {
			answer += (v_sum[i] - v_sum[i - 1]) * i;
		}

		printf("%.4f\n", answer);
	}
}