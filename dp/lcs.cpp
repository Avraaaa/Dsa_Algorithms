#include <bits/stdc++.h>

using namespace std;

#define ll int

// ---------------------------------------------------------
// 1. TOP-DOWN APPROACH (Memoization)
// ---------------------------------------------------------

// Helper function that does the actual recursion
int lcsMemoHelper(int ind1, int ind2, const string& str1, const string& str2, vector<vector<int>>& memo) {
    // Base Case: If either string index reaches 0, the longest common subsequence is 0
    if (ind1 == 0 || ind2 == 0) {
        return 0;
    }

    // Step 1: Check if the subproblem has already been solved
    if (memo[ind1][ind2] != -1) {
        return memo[ind1][ind2];
    }

    // Step 2: If the characters match, they are part of the LCS
    if (str1[ind1 - 1] == str2[ind2 - 1]) {
        return memo[ind1][ind2] = 1 + lcsMemoHelper(ind1 - 1, ind2 - 1, str1, str2, memo);
    }

    // Step 3: If they don't match, branch off and take the maximum of moving either index back by 1
    return memo[ind1][ind2] = max(lcsMemoHelper(ind1 - 1, ind2, str1, str2, memo), 
                                  lcsMemoHelper(ind1, ind2 - 1, str1, str2, memo));
}

// Wrapper function to initialize the memoization table
int lcsMemo(string str1, string str2) {
    int n = str1.size();
    int m = str2.size();

    // Create an (n+1) x (m+1) 2D vector initialized with -1
    vector<vector<int>> memo(n + 1, vector<int>(m + 1, -1));

    // Start the recursion from the end of both strings
    return lcsMemoHelper(n, m, str1, str2, memo);
}

// ---------------------------------------------------------
// 2. BOTTOM-UP APPROACH (Tabulation)
// ---------------------------------------------------------

int lcs(string str1, string str2)
{
    int n = str1.size();
    int m = str2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 0;
    }
    for (int i = 0; i <= m; i++)
    {
        dp[0][i] = 0;
    }

    for (int ind1 = 1; ind1 <= n; ind1++)
    {
        for (int ind2 = 1; ind2 <= m; ind2++)
        {
            if (str1[ind1 - 1] == str2[ind2 - 1])
                dp[ind1][ind2] = 1 + dp[ind1 - 1][ind2 - 1];

            else
                dp[ind1][ind2] = max(dp[ind1 - 1][ind2], dp[ind1][ind2 - 1]);
        }
    }

    string s = "";
    int i = n, j = m;
    while (i > 0 && j > 0)
    {
        if (str1[i - 1] == str2[j - 1])
        {
            s += str1[i - 1];
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }
    reverse(s.begin(), s.end());
    cout << "String found via tabulation: " << s << endl;

    return dp[n][m];
}

// ---------------------------------------------------------
// MAIN DRIVER
// ---------------------------------------------------------

void solve()
{
    string s1 = "adadada";
    string s2 = "iasdywsxadadasdcb";

    // Example using Tabulation
    cout << "--- Tabulation Results ---" << endl;
    ll ans_tab = lcs(s1, s2);
    cout << "Length: " << ans_tab << "\n\n";

    // Example using Memoization
    cout << "--- Memoization Results ---" << endl;
    ll ans_memo = lcsMemo(s1, s2);
    cout << "Length: " << ans_memo << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    while (t--)
    {
        solve();
    }
}