#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

int solve() {
    int N, K;
    if (!(cin >> N >> K)) return 0;

    vector<int> heights(N);
    for (int i = 0; i < N; i++) {
        cin >> heights[i];
    }

    // dp[i] will store the minimum cost to reach stone i
    vector<int> dp(N, INT_MAX);

    // Base Case: Starting stone cost is 0
    dp[0] = 0;

    // Fill the DP table
    for (int i = 1; i < N; i++) {
        // Check all stones the frog could have jumped from (up to K stones back)
        for (int j = 1; j <= K; j++) {
            if (i - j >= 0) {
                int cost = dp[i - j] + abs(heights[i] - heights[i - j]);
                dp[i] = min(dp[i], cost);
            } else {
                // If i-j < 0, we've gone past the first stone
                break;
            }
        }
    }

    cout << dp[N - 1] << endl;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}