#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Returns {min_difference, {subset_1, subset_2}}
pair<ll, pair<vector<ll>, vector<ll>>> min_subset_difference(const vector<ll> &arr) {
    ll n = arr.size();
    ll total_sum = 0;
    
    for (ll num : arr) {
        total_sum += num;
    }

    // We only need to check sums up to half of the total sum.
    // If we find a subset close to total_sum / 2, the other subset takes the rest.
    ll target = total_sum / 2;

    // dp[i][j] is true if a subset of the first 'i' elements sums to 'j'
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

    //------------------- Phase 1: DP Initialization -----------------------------
    // A sum of 0 is always possible using an empty subset
    for (ll i = 0; i <= n; i++) {
        dp[i][0] = true;
    }

    //------------------- Phase 2: DP Table Filling -----------------------------
    for (ll i = 1; i <= n; i++) {
        for (ll current_sum = 1; current_sum <= target; current_sum++) {
            
            ll current_num = arr[i - 1];

            if (current_num > current_sum) {
                // Number is too large, copy state from the row above
                dp[i][current_sum] = dp[i - 1][current_sum];
            } 
            else {
                // Can make the sum by either excluding OR including the current number
                dp[i][current_sum] = dp[i - 1][current_sum] || dp[i - 1][current_sum - current_num];
            }
        }
    }

    //------------------- Phase 3: Find the Optimal Split -----------------------
    // Start from the ideal half (target) and walk backwards to find the largest 
    // achievable sum that is <= total_sum / 2.
    ll best_sum = 0;
    for (ll j = target; j >= 0; j--) {
        if (dp[n][j]) {
            best_sum = j;
            break;
        }
    }

    // If Subset 1 has 'best_sum', Subset 2 has the rest. 
    // The difference is: (total_sum - best_sum) - best_sum
    ll min_diff = total_sum - (2 * best_sum);

    //------------------- Phase 4: Path Reconstruction --------------------------
    vector<ll> subset1, subset2;
    vector<bool> used_in_subset1(n, false); // To track which items go where
    
    ll remaining_sum = best_sum;
    for (ll i = n; i > 0 && remaining_sum > 0; i--) {
        
        // If the cell directly above is true, this element wasn't strictly needed for Subset 1
        if (dp[i - 1][remaining_sum]) {
            continue;
        } 
        // Otherwise, this element MUST have been included in Subset 1
        else {
            used_in_subset1[i - 1] = true;
            remaining_sum -= arr[i - 1]; 
        }
    }

    // Sort the original elements into their respective output vectors
    for (ll i = 0; i < n; i++) {
        if (used_in_subset1[i]) {
            subset1.push_back(arr[i]);
        } else {
            subset2.push_back(arr[i]);
        }
    }

    return {min_diff, {subset1, subset2}};
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin >> n;

    vector<ll> arr(n);
    for (ll i = 0; i < n; i++) {
        cin >> arr[i];
    }

    pair<ll, pair<vector<ll>, vector<ll>>> result = min_subset_difference(arr);
    ll min_difference = result.first;
    vector<ll> subset1 = result.second.first;
    vector<ll> subset2 = result.second.second;

    cout << "Minimum Subset Difference: " << min_difference << "\n\n";
    
    cout << "Subset 1: ";
    for (ll i = 0; i < subset1.size(); i++) {
        if (i > 0) cout << " + ";
        cout << subset1[i];
    }
    cout << "\n";

    cout << "Subset 2: ";
    for (ll i = 0; i < subset2.size(); i++) {
        if (i > 0) cout << " + ";
        cout << subset2[i];
    }
    cout << "\n";

    return 0;
}

/* =========================================
SAMPLE INPUT 
=========================================
5
1 6 11 5 2

=========================================
EXPECTED OUTPUT:
=========================================
Minimum Subset Difference: 1

Subset 1: 1 + 6 + 5
Subset 2: 11 + 2
=========================================
*/