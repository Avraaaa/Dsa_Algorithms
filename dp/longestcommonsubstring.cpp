#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Returns the longest contiguous common substring found in both strings
string longest_common_substring(const string &str1, const string &str2) {
    ll len1 = str1.length();
    ll len2 = str2.length();

    // dp[i][j] stores the length of the longest common suffix 
    // of the substrings str1[0..i-1] and str2[0..j-1]
    vector<vector<ll>> dp(len1 + 1, vector<ll>(len2 + 1, 0));

    ll max_len = 0;
    ll ending_index = 0; // Tracks the end position of the substring in str1

    //------------------- Phase 1: DP Table Filling -----------------------------
    for (ll i = 1; i <= len1; i++) {
        for (ll j = 1; j <= len2; j++) {
            
            // If the characters match, extend the contiguous streak from the previous diagonal
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                
                // Track the absolute maximum length found anywhere in the table
                if (dp[i][j] > max_len) {
                    max_len = dp[i][j];
                    // Save the index where this longest streak ended (0-indexed relative to str1)
                    ending_index = i - 1; 
                }
            } 
            // If there is a mismatch, the contiguous streak is broken
            else {
                dp[i][j] = 0; 
            }
        }
    }

    //------------------- Phase 2: String Reconstruction -------------------------
    // If no common substring exists, return an empty string
    if (max_len == 0) {
        return "";
    }

    // Since we know where the longest streak ended and how long it is,
    // we simply slice it out of the original string.
    // The starting index is (end - length + 1).
    ll starting_index = ending_index - max_len + 1;
    
    return str1.substr(starting_index, max_len);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string str1, str2;
    cin >> str1 >> str2;

    string common_substr = longest_common_substring(str1, str2);

    if (common_substr.empty()) {
        cout << "No common substring found.\n";
    } else {
        cout << "Longest Common Substring: " << common_substr << "\n";
        cout << "Length: " << common_substr.length() << "\n";
    }

    return 0;
}

/* =========================================
SAMPLE INPUT 
=========================================
DEADBEEF
EATBEEFBAD

=========================================
EXPECTED OUTPUT:
=========================================
Longest Common Substring: BEEF
Length: 4
=========================================
*/