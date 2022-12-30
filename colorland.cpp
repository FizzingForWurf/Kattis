
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

int main() {
    int N; cin >> N;
    vector<string> board;
    vector<vector<int>> AL(N+1, vector<int>());
    unordered_map<string, int> last_pos;
    
    board.push_back(""); // Push starting tile
    while (N--) {
        string color; cin >> color;
        board.push_back(color);
    }
    
    // Populate graph by storing the last position of each color 
    // Add each last pos as the neighbouring node to each tile
    for (int i = board.size()-1; i >= 0; i--) {
        for (auto &[color, pos] : last_pos) 
            AL[i].push_back(pos);
            
        // Store the position of the color
        string tile = board[i];
        last_pos[tile] = i;
    }
    
    const int INF = 1e9; // INF = 1B, not 2^31-1 to avoid overflow
    vector<int> dist(AL.size(), INF); dist[0] = 0;
    queue<int> q; q.push(0);
    
    // Perform BFS on unweighted graph
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int &neighbour : AL[u])
            if (dist[neighbour] == INF) {
                dist[neighbour] = dist[u]+1; // dist[v] != INF now
                q.push(neighbour);           // for next iteration
            }
    }
    
    // Return the shortest dist to last node
    cout << dist.back() << '\n';
    
    return 0;
}
