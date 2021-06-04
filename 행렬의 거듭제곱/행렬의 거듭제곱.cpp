#include <iostream>
#include <vector>

using namespace std;

struct matrix {
    vector<vector<long long>> square;

    matrix(int n) {
        square.assign(n, vector<long long>(n));
        for (int i = 0; i < n; i++) {
            square[i][i] = 1;
        }
    }

    friend matrix operator*(const matrix& left, const matrix& right);
    friend ostream& operator<<(ostream& os, const matrix& A);
};

matrix operator*(const matrix& left, const matrix& right) {
    matrix result(left.square.size());
    for (int i = 0; i < left.square.size(); i++) {
        for (int j = 0; j < left.square.size(); j++) {
            long long sum = 0;
            for (int k = 0; k < left.square.size(); k++) {
                sum += ((left.square[i][k] * right.square[k][j]) % 1000);
            }
            result.square[i][j] = (sum % 1000);
        }
    }

    return result;
}

ostream& operator<<(ostream& os, const matrix& A) {
    for (int i = 0; i < A.square.size(); i++) {
        for (int j = 0; j < A.square.size(); j++) {
            os << (A.square[i][j] % 1000) << ' ';
        }
        os << '\n';
    }

    return os;
}

matrix pow(const matrix& A, long long m) {
    if (m == 0)  return matrix{ static_cast<int>(A.square.size()) };
    if (m % 2 > 0)   return pow(A, m - 1) * A;
    matrix half = pow(A, m / 2);
    return half * half;
}

int main() {
    ios::sync_with_stdio(false);	cin.tie(NULL);
    long long N, B;   cin >> N >> B;
    
    matrix A(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> A.square[i][j];
        }
    }

    cout << pow(A, B);
    
    return 0;
}