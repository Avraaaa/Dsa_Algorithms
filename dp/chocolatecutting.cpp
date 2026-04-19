#include <iostream>
#include <vector>
#include <algorithm> // Required for std::max

using namespace std;

// Using the built-in std::max or keeping your custom one
int max_val(int a, int b) {
    return (a > b) ? a : b;
}

// Function signature updated to use a reference to a 2D vector
int solveChocolate(int m, int n, const vector<vector<int>>& prices) {
    // Initializing a 2D vector of size (m+1) x (n+1) filled with 0s
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            // Base case: Price of the piece without any cuts
            dp[i][j] = prices[i][j]; 

            // Horizontal Cuts: Split the height 'i' into 'k' and 'i-k'
            for (int k = 1; k <= i / 2; k++) {
                dp[i][j] = max_val(dp[i][j], dp[k][j] + dp[i - k][j]);
            }

            // Vertical Cuts: Split the width 'j' into 'k' and 'j-k'
            for (int k = 1; k <= j / 2; k++) {
                dp[i][j] = max_val(dp[i][j], dp[i][k] + dp[i][j - k]);
            }
        }
    }

    return dp[m][n];
}

int main() {
    int m = 4;
    int n = 4;
    
    // Create a 2D vector for prices: (m+1) rows, each containing (n+1) ints
    vector<vector<int>> prices(m + 1, vector<int>(n + 1));

    // Fill prices with the default i * j
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            prices[i][j] = i * j; 
        }
    }

    // Assign the "special" high-value piece
    prices[2][2] = 100;

    // Standard C++ output
    cout << "Max Revenue: " << solveChocolate(m, n, prices) << endl;

    // No free() needed! Vectors clean themselves up when they go out of scope.
    return 0;
}