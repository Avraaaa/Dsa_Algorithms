#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int INF = 1e8; 

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t; 
    
    while (t--) {
        int n = 4; // Rows
        int m = 5; // Columns
        int arr[4][5];
        int dp[4][5];

        // 1. Read the grid
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> arr[i][j];
            }
        }

        // 2. Base Case: The top row's cost is simply the values in the top row
        for (int j = 0; j < m; j++) {
            dp[0][j] = arr[0][j];
        }

        // 3. Iterative DP: Build the table row by row, from top to bottom
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                
                
                // Check if coming from the upper-left is valid
                int downLeft = INF;
                if (j > 0) {
                    downLeft = dp[i - 1][j - 1];
                }

                // Coming straight from above is always valid because j is unchanged
                int straight = dp[i - 1][j];

                // Check if coming from the upper-right is valid
                int downRight = INF;
                if (j < m - 1) {
                    downRight = dp[i - 1][j + 1];
                }
                
                // ---------------------------------------------------

                // The cost to reach the current cell is its own value plus the cheapest parent
                dp[i][j] = arr[i][j] + min({downLeft, straight, downRight});
            }
        }

        // 4. Find the minimum cost in the very bottom row
        int minTotalCost = INF;
        int endCol = -1;
        for (int j = 0; j < m; j++) {
            if (dp[n - 1][j] < minTotalCost) {
                minTotalCost = dp[n - 1][j];
                endCol = j; // Remember where the optimal path ended
            }
        }

        cout << "Result (Minimum Sum): " << minTotalCost << "\n\n";

        cout << "Computed DP Table (Costs to reach each cell from the top):\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << dp[i][j] << "\t";
            }
            cout << "\n";
        }
        cout << "\n";

        // 5. Backtrack from the bottom row up to the top row to find the path
        vector<int> optimalPath;
        int currCol = endCol;
        
        for (int i = n - 1; i >= 0; i--) {
            // Record the value of the actual grid cell we are on
            optimalPath.push_back(arr[i][currCol]);
            
            if (i == 0) break; // Reached the top row

            // What was the cumulative cost of the parent cell we came from?
            int targetParentCost = dp[i][currCol] - arr[i][currCol];

            // Check which of the 3 parents above us had this exact target cost
            if (currCol > 0 && dp[i - 1][currCol - 1] == targetParentCost) {
                currCol = currCol - 1; // We came from the upper-left
            } 
            else if (currCol < m - 1 && dp[i - 1][currCol + 1] == targetParentCost) {
                currCol = currCol + 1; // We came from the upper-right
            } 
            else {
                // currCol remains the same, meaning we came straight down
            }
        }

        // The path was collected from bottom to top, so reverse it to print top to bottom
        reverse(optimalPath.begin(), optimalPath.end());

        cout << "Path Trace (Top to Bottom):\n";
        for (int val : optimalPath) {
            cout << val << "\n";
        }
    }
    
    return 0;
}