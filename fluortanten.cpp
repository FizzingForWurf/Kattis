#include <iostream>
using namespace std;

int main() {
    int n; cin >> n;
    
    int index = 1;
    long prev_max = 0, accum = 0, front;
    while (n--) {
        int a; cin >> a;
        if (a == 0) continue;
        
        front = prev_max + a * (index+1); // For putting Bjorn in front of this person
        accum += a * index; // For putting Bjorn at the behind this person
        
        prev_max = front > accum ? front : accum;
        ++index;
    }
    
    cout << prev_max << endl;
    return 0;
}
