#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <unordered_set>
using namespace std;
typedef pair<int, int> pair_ii;

/*
Jurassic Jigsaw

Question: https://open.kattis.com/problems/jurassicjigsaw
Solution: Minimum spanning tree with k weights (where k is small)
Time complexity: O(n^2 * k) given n dna strings of k length

1. Populate adjacency list with neighbours and weights (unlikeliness) for each dna string

2. Apply Prim's algorithm but instead of using a priority queue greedily get minimum 
edge, use an array of k buckets to store each edge to their corresponding weight

3. So in each iteration, find the smallest bucket to find the minimum edge by searching from
the left of the array of k buckets. O(1) time since no. of buckets k is small

4. When pushing in new potential edges, insert into the bucket according to the weight of 
the edge
*/

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input/jurassicjigsaw.txt", "r", stdin);

    int n, k; cin >> n >> k;
    vector<string> dna_mapping(n);

    // similarity -> list of 2 string pairs (include no diff)
    vector<vector<pair_ii>> unlikeliness(k+1); 
    vector<vector<pair_ii>> AL(n, vector<pair_ii>());
    
    for (int num = 0; num < n; num++) {
        string dna; cin >> dna;
        dna_mapping[num] = dna;
    }
    
    // Iterate through each dna combination
    for (int i = 0; i < n; i++) {
        string dna = dna_mapping[i];
        for (int j = 0; j < n; j++) {
            if (i == j) continue;

            int diff = 0;
            for (int l = 0; l < k; l++) // Find similarities
                diff += (dna[l] != dna_mapping[j][l]);

            AL[i].push_back({ j, diff }); // Populate adjacency list
        }
    }

    // Find minimum spanning tree
    vector<bool> visited(n, false);
    int max_mst_edges = n-1; // Max edges = V-1
    int result = 0, edge_count = 0;
    vector<pair_ii> edges_result;

    // Add neighbours of the FIRST node to pq
    visited[0] = true;
    for (auto &[neighbour, diff] : AL[0])
        unlikeliness[diff].push_back({ 0, neighbour });

    // Iterate V-1 times since MST once can have V-1 edges & there is always a valid solution 
    while (edge_count < max_mst_edges) {
        int min_similarity = 0;
        while (unlikeliness[min_similarity].empty()) min_similarity++;

        pair_ii min_edge = unlikeliness[min_similarity].back(); 
        unlikeliness[min_similarity].pop_back();
        int next_dna = min_edge.second;

        // Ignore if node is visited before
        if (visited[next_dna]) continue;
          
        // Destination node has not been visited before
        result += min_similarity;
        edges_result.push_back(min_edge);
        edge_count++;
        
        // Add neighbours of current node into pq
        visited[next_dna] = true;
        for (auto &[neighbour, diff] : AL[next_dna]) {
            if (visited[neighbour]) continue;
            unlikeliness[diff].push_back({ next_dna, neighbour });
        }
    }

    cout << result << '\n';
    for (auto &[from, to] : edges_result) 
        cout << (from < to ? from : to) << " " << (from < to ? to : from) << '\n';
    cout << '\n';

    return 0;
}