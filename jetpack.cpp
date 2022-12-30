#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <stack>
using namespace std;
typedef pair<int, int> ii;

vector<vector<char>> game;

vector<ii> getPossibleMoves(int row, int col) {
    vector<ii> moves;

    if (row == 0) { // Top row (ceiling)
        if (game[row][col+1] == '.') moves.push_back({row, col+1});
        if (game[row+1][col+1] == '.') moves.push_back({row+1, col+1});
    } else if (row == 9) { // Bottom row (floor)
        if (game[row][col+1] == '.') moves.push_back({row, col+1});
        if (game[row-1][col+1] == '.') moves.push_back({row-1, col+1});
    } else { // In the middle
        if (game[row-1][col+1] == '.') moves.push_back({row-1, col+1});
        if (game[row+1][col+1] == '.') moves.push_back({row+1, col+1});
    }

    return moves;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input/jetpack.txt", "r", stdin);

    int N; cin >> N;
    game.assign(10, vector<char>(N));
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < N; j++) {
            char tile; cin >> tile;
            game[i][j] = tile;
        }
    }

    vector<vector<bool>> visited(10, vector<bool>(N, false));
    vector<vector<ii>> parent(10, vector<ii>(N));
    queue<ii> q; q.push({ 9, 0 }); // Push bottom left starting tile
    
    // Perform BFS on unweighted graph, DFS would work too
    while (!q.empty()) {
        ii current = q.front(); q.pop();
        if (current.second == N-1) break; // Terminate early if reached last col

        vector<ii> possible_moves = getPossibleMoves(current.first, current.second);
        for (auto &[row, col] : possible_moves){
            if (!visited[row][col]) {
                parent[row][col] = current;
                visited[row][col] = true;
                q.push({row, col});
            }
        }
    }

    bool valid = false;
    int moves = 0, time = 0;
    stack<ii> result; // start location, duration

    for (int r = 0; r < 10; r++) {
        if (visited[r][N-1]) {
            valid = true;

            ii cur = { r, N-1 }, start = { 9, 0 };
            while (cur != start) { // Traverse parent for path taken
                int cur_r = cur.first, cur_c =  cur.second;
                ii prev = parent[cur_r][cur_c];

                if (cur_r < prev.first || (cur_r == 0 and prev.first == 0)) { 
                    // Up move made as cur pos is higher than previous pos
                    time++;
                } else if (time != 0) { // Down move
                    // Only push move when there was a prev up move
                    result.push({ cur_c, time });
                    time = 0;
                }
                cur = prev;
            }

            if (time != 0) // Record up move from start
                result.push({ 0, time });

            break;
        }
    }

    if (!valid) 
        cout << "No valid path!" << '\n';
    else {
        cout << result.size() << '\n';
        while (!result.empty()) {
            ii move = result.top();
            cout << move.first << " " << move.second << '\n';
            result.pop();
        }
    }

    return 0;
}
