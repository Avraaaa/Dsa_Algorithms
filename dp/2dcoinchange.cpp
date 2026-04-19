#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void traceback2D(const vector<vector<int>>& first, const vector<int>& coins, int target) {
    int i = coins.size();
    int j = target;

    if (first[i][j] == -1) {
        cout << "No solution possible." << endl;
        return;
    }

    cout << "Coins used: ";
    while (j > 0 && i > 0) {
        int coin = first[i][j];
        if (coin == 0) {
            i--; // move to previous coin type
        } else {
            cout << coin << " ";
            j -= coin;
        }
    }
    cout << endl;
}

void coinChange2D(const vector<int>& coins, int target) {
    int n = coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(target + 1, target + 1));
    vector<vector<int>> first(n + 1, vector<int>(target + 1, -1));

    for (int i = 0; i <= n; i++) dp[i][0] = 0; // 0 coins to make 0

    for (int i = 1; i <= n; i++) {
        int coin = coins[i - 1];
        for (int j = 1; j <= target; j++) {
            // Don't use current coin
            dp[i][j] = dp[i - 1][j];
            first[i][j] = 0; // 0 indicates "skip this coin"

            // Use current coin if possible
            if (j >= coin && dp[i][j - coin] + 1 < dp[i][j]) {
                dp[i][j] = dp[i][j - coin] + 1;
                first[i][j] = coin;
            }
        }
    }

    if (dp[n][target] > target) {
        cout << "Impossible to make sum." << endl;
    } else {
        cout << "Minimum coins: " << dp[n][target] << endl;
        traceback2D(first, coins, target);
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

    coinChange2D(coins, target);
    return 0;
}
