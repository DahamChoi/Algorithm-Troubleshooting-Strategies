#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

vector<vector<int>> clock_switch = {
		{0,1,3,4},{0,1,2},{1,2,4,5},{0,3,6},{1,3,4,5,7},
		{2,5,8},{3,4,6,7},{6,7,8},{4,5,7,8}
};

bool is_safe(vector<int>& clocks) {
	return (accumulate(clocks.begin(), clocks.end(), 0) == 0);
}

void push_switch(vector<int>& clocks, int switch_number, int cnt) {
	for (int i = 0; i < cnt; i++) {
		for (auto& it : clock_switch[switch_number]) {
			clocks[it] = (clocks[it] + 1 >= 4 ? 0 : clocks[it] + 1);
		}
	}
}

vector<int> answer_history;
void func(vector<int>& clocks, int index, int depth, vector<int>& history) {
	if (index >= clock_switch.size()) {
		if (is_safe(clocks) && (answer_history.empty() || history.size() < answer_history.size())) {
			answer_history = history;
		}
		return;
	}

	for (int i = 0; i <= 3; i++) {
		vector<int> before = clocks;
		push_switch(clocks, index, i);
		for (int j = 0; j < i; j++) {
			history.push_back(index);
		}
		func(clocks, index + 1, depth + i, history);
		clocks = before;
		for (int j = 0; j < i; j++) {
			history.pop_back();
		}
	}
}

int main() {
	vector<int> clocks(9);

	for (int i = 0; i < 9; i++) {
		cin >> clocks[i];
	}

	vector<int> history;
	func(clocks, 0, 0, history);

	sort(answer_history.begin(), answer_history.end());
	for (auto it : answer_history) {
		cout << (it + 1) << ' ';
	}

	return 0;
}