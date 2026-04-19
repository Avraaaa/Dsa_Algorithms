#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int minEnergy(int n, vector<int>& heights) {
    // dp[i] stores the minimum cost to reach stone i
    vector<int> dp(n, 0);

    // Base Case: Starting stone
    dp[0] = 0;

    for (int i = 1; i < n; i++) {
        // Option 1: Jump from the previous stone
        int jumpOne = dp[i - 1] + abs(heights[i] - heights[i - 1]);

        // Option 2: Jump from two stones back (if possible)
        int jumpTwo = 1e9; // Initialize with a large value
        if (i > 1) {
            jumpTwo = dp[i - 2] + abs(heights[i] - heights[i - 2]);
        }

        // Take the minimum of the two possible jumps
        dp[i] = min(jumpOne, jumpTwo);
    }

    return dp[n - 1];
}

int main() {
    int n;
    cout << "Enter number of stones: ";
    cin >> n;

    vector<int> heights(n);
    cout << "Enter heights of the stones: ";
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }

    cout << "Minimum energy required: " << minEnergy(n, heights) << endl;

    return 0;
}