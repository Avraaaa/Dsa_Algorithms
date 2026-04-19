#include <iostream>
#include <vector>
 
using namespace std;
 
void coinChangeWays(const vector<int>& coins, int target) {
    // dp[i] will store the total NUMBER OF WAYS to make the amount i.
    // Initialize the array with 0s because we start with 0 known ways.
    vector<long long> dp(target + 1, 0); 
 
    // Base case: There is exactly 1 way to make a target of 0 (use no coins).
    dp[0] = 1;
 
    // Notice the loop order is flipped compared to the minimum coins problem!
    // We loop over coins FIRST to ensure we only count combinations (e.g., 1+2), 
    // and don't double-count permutations (e.g., counting 1+2 and 2+1 as two different ways).
    for (int coin : coins) {
        for (int i = coin; i <= target; i++) {
            // The transition: The number of ways to make amount 'i' is its current ways 
            // PLUS the number of ways to make the remainder (i - coin).
            dp[i] += dp[i - coin];
        }
    }
 
    cout << "Total possible ways: " << dp[target] << endl;
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
 
    coinChangeWays(coins, target);
    return 0;
}