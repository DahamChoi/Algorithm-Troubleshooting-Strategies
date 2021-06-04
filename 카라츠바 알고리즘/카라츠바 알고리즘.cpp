#include <iostream>
#include <vector>
#include <string>

using namespace std;

void normalize(vector<int>& num) {
	num.push_back(0);

	for (int i = 0; i + 1 < num.size(); i++) {
		if (num[i] < 0) {
			int borrow = (abs(num[i]) + 9) / 10;
			num[i + 1] -= borrow;
			num[i] += borrow * 10;
		}
		else {
			num[i + 1] += num[i] / 10;
			num[i] %= 10;
		}
	}

	while (!num.empty() && num.back() == 0) {
		num.pop_back();
	}
}

// a += b * (10^k);
void addTo(vector<int>& a, const vector<int>& b, int k) {
	while (a.size() < b.size() + k) {
		a.push_back(0);
	}

	for (int i = 0; i < b.size(); i++) {
		a[i + k] += b[i];
	}

	normalize(a);
}

// a -= b;	(a >= b)
void subFrom(vector<int>& a, const vector<int>& b) {
	for (int i = 0; i < b.size(); i++) {
		a[i] -= b[i];
	}

	normalize(a);
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<int> c(a.size() + b.size() + 1, 0);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			c[i + j] += a[i] * b[j];
		}
	}

	normalize(c);
	return c;
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
	int an = a.size(), bn = b.size();
	// a가 b보다 짧을 경우 둘을 바꾼다.
	if (an < bn) return karatsuba(b, a);
	// 기저 사례 : a나 b가 비어 있는 경우
	if (an == 0 || bn == 0)	return {};
	// 기저 사례 a가 비교적 짧은 경우 O(n^2) 곱셈으로 변경한다.
	if (an <= 50)	return multiply(a, b);
	
	int half = an / 2;

	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());

	vector<int> z2 = karatsuba(a1, b1);
	vector<int> z0 = karatsuba(a0, b0);
	
	addTo(a0, a1, 0);	addTo(b0, b1, 0);

	vector<int> z1 = karatsuba(a0, b0);
	
	subFrom(z1, z0);
	subFrom(z1, z2);

	vector<int> ref;
	addTo(ref, z0, 0);
	addTo(ref, z1, half);
	addTo(ref, z2, half + half);
	return ref;
}

int main() {
	string A(100000,'A'), B(100000,'B');	//cin >> A >> B;
	vector<int> a(A.length()), b(B.length());
	for (int i = 0; i < A.length(); i++) {
		a[A.length() - i - 1] = (A[i] - '0');
	}

	for (int i = 0; i < B.length(); i++) {
		b[B.length() - i - 1] = (B[i] - '0');
	}

	vector<int> answer = karatsuba(a, b);
	for (auto it = answer.rbegin(); it != answer.rend(); it++) {
		cout << (*it);
	}

	return 0;
}