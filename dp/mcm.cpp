#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Function to print the optimal parenthesization
// s: The split table computed by the DP function
// i: Start index of the chain
// j: End index of the chain
void printOptimalParens(const vector<vector<int>>& s, int i, int j) {
    if (i == j) {
        cout << "A" << i;
    } else {
        cout << "(";
        // Recursively print left part from i to s[i][j]
        printOptimalParens(s, i, s[i][j]);
        // Recursively print right part from s[i][j] + 1 to j
        printOptimalParens(s, s[i][j] + 1, j);
        cout << ")";
    }
}

// Function to calculate minimum number of multiplications
// p: Array of dimensions. Matrix Ai has dimensions p[i-1] x p[i]
// n: Number of matrices (size of p is n + 1)
void matrixChainOrder(const vector<int>& p) {
    int n = p.size() - 1; // Number of matrices

    // m[i][j] stores the minimum number of scalar multiplications 
    // needed to compute the matrix A[i]...A[j]
    vector<vector<int>> m(n + 1, vector<int>(n + 1));

    // s[i][j] stores the index k at which the optimal split occurs
    vector<vector<int>> s(n + 1, vector<int>(n + 1));

    // Cost is zero when multiplying one matrix
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    // L is the chain length
    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            
            // Try every possible split point k between i and j
            for (int k = i; k <= j - 1; k++) {
                // Cost = cost(left) + cost(right) + cost(multiplication)
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k; // Record the split point
                }
            }
        }
    }

    // Output results
    cout << "Minimum number of multiplications: " << m[1][n] << endl;
    cout << "Optimal Parenthesization: ";
    printOptimalParens(s, 1, n);
    cout << endl;
}

int main() {
    // Example dimensions:
    // A1: 30x35
    // A2: 35x15
    // A3: 15x5
    // A4: 5x10
    // A5: 10x20
    // A6: 20x25
    vector<int> p = {30, 35, 15, 5, 10, 20, 25};

    matrixChainOrder(p);

    return 0;
}