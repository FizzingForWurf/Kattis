#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main() {
    int t; cin >> t; cin.ignore(); 
    
    while (t--) {
        // Get raw number data
        vector<vector<int>> data(2, vector<int>());
        for (int i = 0; i < 2; i++) {
            string line; getline(cin, line);
            stringstream ss(line); // Splits line by " "
            
            string num; 
            while (ss >> num) {
                int digit = stoi(num); // Converts string to int
                data[i].push_back(digit);
            }
        }
        
        // Interpret number data
        vector<int> integer(2, 0);
        for (int i = 0; i < 2; i++) {
            int place = 1;
            for (int j = data[i].size()-1; j >= 0; j--) {
                integer[i] += data[i][j] * place;
                place *= 10;
            }
        }
        
        int result = integer[0] + integer[1];
        string show = to_string(result);
        for (char num : show) 
            cout << num << " ";
        cout << '\n';
    }
    
    return 0;
}