#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/*
1. The Question Mark (?)

Rule: Matches exactly one of any character.

2. The Asterisk / Star (*)

Rule: Matches zero or more of any sequence of characters.

*/
bool wildcard_matching(const string &text, const string &pattern) {
    ll n = text.length();
    ll m = pattern.length();

    // dp[i][j] is true if the first 'i' characters of the text 
    // match the first 'j' characters of the pattern.
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

    //------------------- Phase 1: DP Initialization -----------------------------
    // Base Case 1: Empty text matches an empty pattern
    dp[0][0] = true;

    // Base Case 2: Empty text can only match a pattern if the pattern is entirely '*'
    for (ll j = 1; j <= m; j++) {
        if (pattern[j - 1] == '*') {
            dp[0][j] = dp[0][j - 1]; // Inherit from the previous state
        } else {
            break; // The moment we hit a non-'*', the rest of the empty text matches fail
        }
    }

    //------------------- Phase 2: DP Table Filling -----------------------------
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= m; j++) {
            
            // If the characters match exactly, OR the pattern has a '?' (wildcard single character)
            if (text[i - 1] == pattern[j - 1] || pattern[j - 1] == '?') {
                dp[i][j] = dp[i - 1][j - 1];
            }
            // If the pattern has a '*', it has two magical properties. It can act as:
            // 1. An empty sequence (we ignore the '*' -> look left: dp[i][j-1])
            // 2. Any character sequence (we consume one character from the text -> look up: dp[i-1][j])
            else if (pattern[j - 1] == '*') {
                dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
            }
            // Absolute mismatch
            else {
                dp[i][j] = false;
            }
        }
    }

    return dp[n][m];
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string text, pattern;
    cin >> text >> pattern;

    bool is_match = wildcard_matching(text, pattern);

    if (is_match) {
        cout << "Match Successful!\n";
    } else {
        cout << "Match Failed.\n";
    }

    return 0;
}

/* =========================================
SAMPLE INPUT 1 
=========================================
adceb
*a*b

=========================================
EXPECTED OUTPUT 1:
=========================================
Match Successful!

=========================================
SAMPLE INPUT 2 
=========================================
cb
?a

=========================================
EXPECTED OUTPUT 2:
=========================================
Match Failed.
=========================================
*/