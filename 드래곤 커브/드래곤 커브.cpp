#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// 초기 문자열 seed를 generations세대 진화한 결과를 출력
void curve(const string& seed, int generations) {
	// 기저 사례
	if (generations == 0) {
		cout << seed;
		return;
	}

	for (int i = 0; i < seed.size(); i++) {
		if (seed[i] == 'X') {
			curve("X+YF", generations - 1);
		}
		else if (seed[i] == 'Y') {
			curve("FX-Y", generations - 1);
		}
		else {
			cout << seed[i];
		}
	}
}

const int MAX = 1000000000 + 1;
// length[i] = X나 Y를 i번 치환한 후의 길이
int length[51];
void precalc() {
	length[0] = 1;
	for (int i = 1; i <= 50; i++) {
		length[i] = min(MAX, length[i - 1] * 2 + 2);
	}
}

const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";

// dragonCurve를 generations 진화시킨 결과에서 skip번째 문자를 반환한다.
char expand(const string& dragonCurve, int generations, int skip) {
	if (generations == 0) {
		assert(skip < dragonCurve.size());
		return dragonCurve[skip];
	}

	for (int i = 0; i < dragonCurve.size(); i++) {
		if (dragonCurve[i] == 'X' || dragonCurve[i] == 'Y') {
			if (skip >= length[generations]) {
				skip -= length[generations];
			}
			else if (dragonCurve[i] == 'X') {
				return expand(EXPAND_X, generations - 1, skip);
			}
			else {
				return expand(EXPAND_Y, generations - 1, skip);
			}
		}
		else if (skip > 0) {
			--skip;
		}
		else {
			return dragonCurve[i];
		}
	}

	return '#';
}

int main() {

	return 0;
}