#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int INF = 1e8; // Represents an invalid path out of bounds

// Global Variables
int n = 4; 
int m = 5; 
int arr[4][5]; 
int dp[4][5];  
vector<ll> optimalPath; 

// ---------------------------------------------------------
// HELPER FUNCTIONS (Kept outside main for clean recursion)
// ---------------------------------------------------------

// Computes the minimum path sum from cell (i, j) downwards
int findMinPath(int i, int j) {
    if (j < 0 || j >= m) return INF; // Out of bounds
    if (i == n - 1) return arr[i][j]; // Reached bottom row
    if (dp[i][j] != -1) return dp[i][j]; // Return memoized result

    int minNextCost = INF;
    minNextCost = min(minNextCost, findMinPath(i + 1, j - 1)); // Down-Left
    minNextCost = min(minNextCost, findMinPath(i + 1, j + 1)); // Down-Right
    minNextCost = min(minNextCost, findMinPath(i + 1, j));     // Straight Down
    
    return dp[i][j] = minNextCost + arr[i][j];
}

// Backtracks to record the optimal path taken
void printBestPath(int i, int j) {
    optimalPath.push_back(arr[i][j]);
    
    if (i == n - 1) return; // Reached bottom row
    
    int targetNextCost = dp[i][j] - arr[i][j]; 
    
    if (j - 1 >= 0 && dp[i + 1][j - 1] == targetNextCost) {
        printBestPath(i + 1, j - 1);
    } 
    else if (j + 1 < m && dp[i + 1][j + 1] == targetNextCost) {
        printBestPath(i + 1, j + 1);
    } 
    else {
        printBestPath(i + 1, j);
    }
}

// ---------------------------------------------------------
// MAIN EXECUTABLE (Combined main + solve)
// ---------------------------------------------------------

int main() {
    // 1. Fast I/O Setup
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);

    int t = 1; 
    // cin >> t; // Uncomment if your input provides the number of test cases
    
    while (t--) {
        // [CRITICAL ADDITION] Clear the global vector for each new test case
        optimalPath.clear(); 

        // 2. Read grid and initialize DP table
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> arr[i][j];
                dp[i][j] = -1;
            }
        }
        
        // 3. Calculate minimum cost starting from any cell in the top row
        int overallMinCost = INF;
        for (int j = 0; j < m; j++) {
            overallMinCost = min(overallMinCost, findMinPath(0, j));
        }
        
        cout << "Result (Minimum Sum): " << overallMinCost << "\n\n";
        
        // 4. Locate the starting column that yielded the minimum cost
        int startCol = -1;
        for (int j = 0; j < m; j++) {
            if (dp[0][j] == overallMinCost) {
                startCol = j;
                break; 
            }
        }
        
        // 5. Output the complete DP table
        cout << "Computed DP Table:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // Formatting for cleaner console output
                cout << dp[i][j] << "\t"; 
            }
            cout << "\n";
        }
        cout << "\n";

        // 6. Trace and print the optimal path
        cout << "Path Trace (Reversed):\n";
        printBestPath(0, startCol);

        for (int i = optimalPath.size() - 1; i >= 0; i--) {
            cout << optimalPath[i] << "\n";
        }
    }
    
    return 0;
}

/*
9 2 8 7 3
1 9 9 2 9
9 2 9 9 9
9 9 1 9 9

*/