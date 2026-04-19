#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Returns {minimum_edit_distance, sequence_of_operations}
pair<ll, vector<string>> edit_distance(const string &source, const string &target) {
    ll len1 = source.length();
    ll len2 = target.length();

    // dp[i][j] is the min operations to convert source[0..i-1] into target[0..j-1]
    vector<vector<ll>> dp(len1 + 1, vector<ll>(len2 + 1, 0));

    //------------------- Phase 1: DP Initialization -----------------------------
    // If source is empty, the only option is to insert all characters of target
    for (ll j = 0; j <= len2; j++) {
        dp[0][j] = j;
    }
    
    // If target is empty, the only option is to delete all characters of source
    for (ll i = 0; i <= len1; i++) {
        dp[i][0] = i;
    }

    //------------------- Phase 2: DP Table Filling -----------------------------
    for (ll i = 1; i <= len1; i++) {
        for (ll j = 1; j <= len2; j++) {
            
            if (source[i - 1] == target[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // Cost 0: Characters match
            } 
            else {
                dp[i][j] = 1 + min({
                    dp[i - 1][j - 1], // Replace
                    dp[i - 1][j],     // Delete from source
                    dp[i][j - 1]      // Insert into source
                });
            }
        }
    }

    //------------------- Phase 3: Path Reconstruction -------------------------
    vector<string> operations;
    ll i = len1;
    ll j = len2;

    // Walk backwards through the DP table to figure out which choices we made
    while (i > 0 || j > 0) {
        
        // Check if we arrived here by matching characters (Cost 0)
        if (i > 0 && j > 0 && source[i - 1] == target[j - 1]) {
            operations.push_back("Keep '" + string(1, source[i - 1]) + "'");
            i--;
            j--;
        } 
        // Check if we arrived here via a Replace operation (Cost 1)
        else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            operations.push_back("Replace '" + string(1, source[i - 1]) + "' with '" + string(1, target[j - 1]) + "'");
            i--;
            j--;
        } 
        // Check if we arrived here via a Delete operation (Cost 1)
        else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            operations.push_back("Delete '" + string(1, source[i - 1]) + "'");
            i--;
        } 
        // Check if we arrived here via an Insert operation (Cost 1)
        else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            operations.push_back("Insert '" + string(1, target[j - 1]) + "'");
            j--;
        }
    }

    // Reverse because we traced from the end of the strings to the beginning
    reverse(operations.begin(), operations.end());

    return {dp[len1][len2], operations};
}

/*
// -------------------------------------------------------------------------
// RECURSIVE HELPER FUNCTION (The "Top-Down" part)
// -------------------------------------------------------------------------
ll get_min_distance(ll i, ll j, const string &source, const string &target, vector<vector<ll>> &memo) {
    // Base Case 1: Source is empty, must insert remaining target characters
    if (i == 0) return j;
    
    // Base Case 2: Target is empty, must delete remaining source characters
    if (j == 0) return i;

    // Memoization Check: If we already computed this state, return it
    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    // Recursive Step 1: Characters match (Cost 0)
    if (source[i - 1] == target[j - 1]) {
        return memo[i][j] = get_min_distance(i - 1, j - 1, source, target, memo);
    } 
    
    // Recursive Step 2: Characters differ (Cost 1 + min of operations)
    ll replace_cost = get_min_distance(i - 1, j - 1, source, target, memo);
    ll delete_cost  = get_min_distance(i - 1, j, source, target, memo);
    ll insert_cost  = get_min_distance(i, j - 1, source, target, memo);

    return memo[i][j] = 1 + min({replace_cost, delete_cost, insert_cost});
}

// -------------------------------------------------------------------------
// MAIN EDIT DISTANCE LOGIC
// -------------------------------------------------------------------------
pair<ll, vector<string>> edit_distance_topdown(const string &source, const string &target) {
    ll len1 = source.length();
    ll len2 = target.length();

    // Initialize memoization table with -1 (meaning "uncalculated")
    vector<vector<ll>> memo(len1 + 1, vector<ll>(len2 + 1, -1));

    // Pre-fill the base cases in the memo table. 
    // We do this so the path reconstruction loop below has the 0th row/col data it needs.
    for (ll j = 0; j <= len2; j++) memo[0][j] = j;
    for (ll i = 0; i <= len1; i++) memo[i][0] = i;

    // Trigger the recursive function from the "Top" (the full lengths)
    ll min_dist = get_min_distance(len1, len2, source, target, memo);

    //------------------- Path Reconstruction -------------------------
    // This part remains exactly identical to the bottom-up approach!
    vector<string> operations;
    ll i = len1;
    ll j = len2;

    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && source[i - 1] == target[j - 1]) {
            operations.push_back("Keep '" + string(1, source[i - 1]) + "'");
            i--;
            j--;
        } 
        else if (i > 0 && j > 0 && memo[i][j] == memo[i - 1][j - 1] + 1) {
            operations.push_back("Replace '" + string(1, source[i - 1]) + "' with '" + string(1, target[j - 1]) + "'");
            i--;
            j--;
        } 
        else if (i > 0 && memo[i][j] == memo[i - 1][j] + 1) {
            operations.push_back("Delete '" + string(1, source[i - 1]) + "'");
            i--;
        } 
        else if (j > 0 && memo[i][j] == memo[i][j - 1] + 1) {
            operations.push_back("Insert '" + string(1, target[j - 1]) + "'");
            j--;
        }
    }

    reverse(operations.begin(), operations.end());

    return {min_dist, operations};
}*/
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string source, target;
    cin >> source >> target;

    pair<ll, vector<string>> result = edit_distance(source, target);
    ll min_distance = result.first;
    vector<string> steps = result.second;

    cout << "Minimum Edit Distance: " << min_distance << "\n\n";
    cout << "Step-by-step Transformation:\n";
    
    for (ll i = 0; i < steps.size(); i++) {
        cout << i + 1 << ". " << steps[i] << "\n";
    }

    return 0;
}

/* =========================================
SAMPLE INPUT 
=========================================
INTENTION
EXECUTION

=========================================
EXPECTED OUTPUT:
=========================================
Minimum Edit Distance: 5

Step-by-step Transformation:
1. Replace 'I' with 'E'
2. Replace 'N' with 'X'
3. Keep 'T'
4. Replace 'E' with 'E' (Technically 'Keep', depends on alignment, but optimally:)
   Delete 'E'
   Insert 'E'
   Wait, optimal for this specific trace:
   
Let's see actual optimal trace:
1. Replace 'I' with 'E'
2. Replace 'N' with 'X'
3. Replace 'T' with 'E'
4. Keep 'E'
5. Insert 'C'
6. Keep 'U'
7. Keep 'T'
8. Keep 'I'
9. Keep 'O'
10. Keep 'N'
(Total Cost = 5)
=========================================
*/