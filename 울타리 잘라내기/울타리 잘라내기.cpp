#include <iostream>
#include <vector>

using namespace std;

vector<long long> h;

long long solve(int left, int right) {
	if (left == right) return h[left];
	int mid = (left + right) / 2;
	long long ref = max(solve(left, mid), solve(mid + 1, right));
	long long lo = mid, hi = mid + 1;
	long long height = min(h[lo], h[hi]);
	ref = max(ref, height * 2);
	while (left < lo || hi < right) {
		if (hi < right && (lo == left || h[lo - 1] < h[hi + 1])) {
			++hi;
			height = min(height, h[hi]);
		}
		else {
			--lo;
			height = min(height, h[lo]);
		}

		ref = max(ref, height * (hi - lo + 1));
	}

	return ref;
}

int main() {
	ios::sync_with_stdio(false);	cin.tie(NULL);

	while (true) {
		int n;	cin >> n;
		if (n == 0) {
			break;
		}

		h.assign(n, 0);
		for (int i = 0; i < n; i++) {
			cin >> h[i];
		}

		cout << solve(0, n - 1) << '\n';
	}

	return 0;
}