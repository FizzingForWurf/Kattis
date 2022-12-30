#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int A; cin >> A; cin.ignore();
    vector<string> people;
 
    while (A--) {
        string name; cin >> name;
        people.push_back(name);
    }

    sort(people.begin(), people.end());

    int B; cin >> B; cin.ignore();
    while (B--) {
        string nickname; cin >> nickname;
        int lower = lower_bound(people.begin(), people.end(), nickname) - people.begin();
        
        char last_char = nickname.back()+1;
        nickname[nickname.size() - 1] = last_char;
        int upper = lower_bound(people.begin(), people.end(), nickname) - people.begin();

        cout << upper - lower << '\n';
    }

    return 0;
}
