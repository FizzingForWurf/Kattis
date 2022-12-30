#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int, int> ii;

int main() {
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        
        vector<int> labs;
        vector<vector<int>> AL(n, vector<int>());
        vector<int> indegree(AL.size(), 0);
        
        while (n--) {
            int lab; cin >> lab; lab--;
            labs.push_back(lab);
        }
        
        while (m--) {
            int i, j; cin >> i >> j; 
            i--; j--;
            AL[i].push_back(j);
            indegree[j]++;
        }
        
        int start1 = 0, start2 = 0;
        for (int cur = 0; cur <= 1; cur++) {
            vector<int> deg(indegree);
            vector<queue<int>> lab_queue(2, queue<int>());
            
            for (int i = 0; i < indegree.size(); i++)
                if (indegree[i] == 0) {
                    int lab = labs[i];
                    lab_queue[lab].push(i);
                }
            
            int swaps = 0, cur_lab = cur;
            while (!lab_queue[0].empty() or !lab_queue[1].empty()) {
                // Find topo sort within same current lab first
                while (!lab_queue[cur_lab].empty()) {
                    int u = lab_queue[cur_lab].front();
                    lab_queue[cur_lab].pop();
                    
                    for (int v : AL[u]) {
                        if (--deg[v] == 0) {
                            int lab = labs[v];
                            lab_queue[lab].push(v);
                        }
                    }
                }
                cur_lab = !cur_lab; // Change to other lab
                swaps++;
            }
            if (cur == 0) start1 = swaps-1;
            else if (cur == 1) start2 = swaps-1;
        }
        
        cout << min(start1, start2) << '\n';
        
//      priority_queue<ii> q; int start = 0;
//      for (int i = 0; i < indegree.size(); i++)
//          if (indegree[i] == 0) {
//              int weight = 100;
//              
//              if (q.empty()) start = i;
//              else weight = labs[start] != labs[i];
//              
//              q.push({ -weight, i }); // weight, num
//          }
//      
//      int answer = 0;
//      while (!q.empty()) {
//          ii item = q.top();
//          q.pop();
//          
//          answer -= item.first; // Sum weights
//          int u = item.second;
//          for (int v : AL[u]) {
//              if (--indegree[v] == 0) {
//                  int w = labs[u] != labs[v];
//                  q.push({ -w, v });
//              }
//          }
//      }
//      
//      cout << answer-100 << '\n';
    }
    return 0;
}
