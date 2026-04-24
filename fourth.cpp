#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n, m;
    cout << "Введите n и m:";
    cin >> n >> m;
    vector<long long> a(n);
    cout << "Введите числа: ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // Префиксные суммы
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + a[i];
    }
    
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, -1e18));
    
    for (int last = 0; last <= m; last++) {
        dp[n][last] = 0;
    }
    
    for (int i = n - 1; i >= 0; i--) {
        for (int last = 0; last <= m; last++) {
            long long best = -1e18;
            
            for (int k = 1; k <= m && i + k <= n; k++) {
                if (k == last) continue;
                
                long long sum = prefix[i + k] - prefix[i];
                long long diff =  dp[i + k][k] - sum;
                
                if (diff > best) {
                    best = diff;
                }
            }
            
            if (best != -1e18) {
                dp[i][last] = best;
            }
        }
    }
    
    if (dp[0][0] > 0) {
        cout << "1" << endl;
    } else {
        cout << "0" << endl;
    }
    
    return 0;
}
