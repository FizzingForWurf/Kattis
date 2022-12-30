#include <iostream>
#include <vector>
#include <map>
using namespace std;
const int INF = 1e9;

int maximum = 0;
vector<int> game;
vector<vector<int>> AL;
vector<int> result;

int dfs(int node) {
    if (game[node] == maximum) {
        result[node] = 0;
        return 0;
    } else if (result[node] < INF) 
        // Vertex has been visited before, stop traversing
        return result[node];

    int minimum = INF;
    for (int neighbour : AL[node]) {
        int dist = dfs(neighbour) + 1;
        if (dist < minimum) minimum = dist;
    }

    result[node] = minimum;
    return minimum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input/couplecompetition.txt", "r", stdin);

    int N; cin >> N;
    result.assign(N, INF);
    AL.assign(N, vector<int>());
    
    while (N--) {
        int height; cin >> height;
        game.push_back(height);
        
        if (height > maximum) maximum = height;
    }
    
    map<int, int> left_jumps; // height -> index
    for (int i = 0; i < game.size(); i++) {
        int current = game[i];

        auto it = left_jumps.upper_bound(current);
        if (it == left_jumps.end()) 
            left_jumps.clear();
        else {
            int neighbour = (*it).second;
            AL[i].push_back(neighbour);
            left_jumps.erase(left_jumps.begin(), it);
        }
        left_jumps[current] = i;
    }

    map<int, int> right_jumps; // height -> index
    for (int i = game.size()-1; i >= 0; i--) {
        int current = game[i];

        auto it = right_jumps.upper_bound(current);
        if (it == right_jumps.end()) 
            right_jumps.clear();
        else {
            int neighbour = (*it).second;
            AL[i].push_back(neighbour);
            right_jumps.erase(right_jumps.begin(), it);
        }
        right_jumps[current] = i;
    }

    for (int k = 0; k < game.size(); k++) 
        if (result[k] >= INF) dfs(k);
    
    for (int item : result) 
        cout << item << " ";
    cout << endl;
    
    return 0;
}