#include <iostream>
using namespace std;

int main() {
    long long n, K; cin >> n >> K;
    if (n < 2*K) cout << n-1 << '\n';
    else cout << K + (n-1) % K + 1 << '\n';
    return 0;
}
