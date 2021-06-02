#include <iostream>
#include <vector>

using namespace std;

vector<vector<pair<int,int>>> piece = {
    {{0,0},{1,0},{0,1}},{{0,0},{1,0},{1,1}},{{0,0},{0,1},{-1,1}},{{0,0},{0,1},{1,1}}
};

void stuck_piece(const vector<pair<int, int>>& p, vector<string>& board, int x, int y) {
    for (int i = 0; i < p.size(); i++) {
        int nx = p[i].first + x, ny = p[i].second + y;
        board[ny][nx] = '#';
    }
}

void back_tracking(vector<string>& board, int& answer) {
    bool is_clear = true;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.front().size(); j++) {
            if (board[i][j] == '.') {
                is_clear = false;
                for (int k = 0; k < piece.size(); k++) {
                    bool is_safe = true;
                    for (int l = 0; l < piece[k].size(); l++) {
                        int nx = piece[k][l].first + j, ny = piece[k][l].second + i;
                        if (!(ny >= 0 && ny < board.size() && nx >= 0 && nx < board.front().size() && board[ny][nx] == '.')) {
                            is_safe = false;
                            break;
                        }
                    }

                    if (is_safe) {
                        vector<string> before = board;
                        stuck_piece(piece[k], board, j, i);
                        back_tracking(board, answer);
                        board = before;
                    }
                }
                return;
            }
        }
    }

    if (is_clear) {
        ++answer;
    }
}

int solution(vector<string>& board) {
    int answer = 0;
    back_tracking(board, answer);
    return answer;
}

int main() {
    ios::sync_with_stdio(false);	cin.tie(NULL);
    int T;  cin >> T;
    for (int i = 0; i < T; i++) {
        int H, W;   cin >> H >> W;
        vector<string> board(H);
        for (int j = 0; j < H; j++) {
            cin >> board[j];
        }

        cout << solution(board) << '\n';
    }

    return 0;
}

/*
1
3 7
#.....#
#.....#
###..##
*/