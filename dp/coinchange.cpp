#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void traceback(const vector<int>& first, int target) {
    if (target == 0) return;
    
    if (first[target] == -1) {
        cout << "No solution possible." << endl;
        return;
    }

    cout << "Coins used: ";
    int curr = target;
    while (curr > 0) {
        cout << first[curr] << " ";
        curr -= first[curr];
    }
    cout << endl;
}

void coinChange(const vector<int>& coins, int target) {
    vector<int> dp(target + 1, target + 1);
    vector<int> first(target + 1, -1);

    dp[0] = 0;

    for (int i = 1; i <= target; i++) {
        for (int coin : coins) {
            if (i >= coin) {
                if (dp[i - coin] + 1 < dp[i]) {
                    dp[i] = dp[i - coin] + 1;
                    first[i] = coin;
                }
            }
        }
    }

    if (dp[target] > target) {
        cout << "Impossible to make sum." << endl;
    } else {
        cout << "Minimum coins: " << dp[target] << endl;
        traceback(first, target);
    }
}

int main() {
    int n, target;
    cout << "Enter number of coin types: ";
    cin >> n;

    vector<int> coins(n);
    cout << "Enter coin values: ";
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    cout << "Enter target amount: ";
    cin >> target;

    coinChange(coins, target);
    return 0;
}