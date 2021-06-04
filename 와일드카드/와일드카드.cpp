#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

string W, S;
vector<vector<int>> cache;

bool matchMemoized(int w, int s) {
	int& ret = cache[w][s];
	if (ret != -1)	return ret;
	while (s < S.size() && w < W.size() &&
		(W[w] == '?' || W[w] == S[s])) {
		return ret = matchMemoized(w + 1, s + 1);
	}

	if (w == W.size())	return ret = (s == S.size());

	if (W[w] == '*') {
		if (matchMemoized(w + 1, s) ||
			(s < S.size() && matchMemoized(w, s + 1))) {
			return ret = 1;
		}
	}

	return ret = 0;
}

int main() {
	ios::sync_with_stdio(false);	cin.tie(NULL);

	int T;		cin >> T;
	while (T--) {
		cin >> W;
		int N;		cin >> N;
		set<string> files;
		for (int i = 0; i < N; i++) {
			string str;	cin >> str;
			files.insert(str);
		}

		for (auto it = files.begin(); it != files.end(); ) {
			S = *it;
			cache.assign(101, vector<int>(101, -1));

			if (!matchMemoized(0, 0)) {
				it = files.erase(it);
			}
			else {
				it++;
			}
		}

		for (auto& it : files) {
			cout << it << '\n';
		}
	}

	return 0;
}