#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Returns {is_possible, subset_elements}
pair<bool, vector<ll>> subset_sum(const vector<ll> &elements, ll target) {
    ll n = elements.size();

    // dp[i][j] is true if a subset of the first 'i' elements sums to 'j'
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

    // Base case: a target sum of 0 is always possible (empty subset)
    for (ll i = 0; i <= n; i++) {
        dp[i][0] = true;
    }

    for (ll i = 1; i <= n; i++) {
        for (ll current_sum = 1; current_sum <= target; current_sum++) {
            
            ll current_num = elements[i - 1];

            if (current_num > current_sum) {
                // Number is too large to include, copy state from above
                dp[i][current_sum] = dp[i - 1][current_sum];
            } 
            else {
                // Can make the sum by either excluding OR including the current number
                dp[i][current_sum] = dp[i - 1][current_sum] || dp[i - 1][current_sum - current_num];
            }
        }
    }

    vector<ll> chosen_subset;
    
    // If target is unreachable, return early
    if (!dp[n][target]) {
        return {false, chosen_subset};
    }

    // Backtrack through the DP table to reconstruct the chosen elements
    ll remaining_sum = target;
    for (ll i = n; i > 0 && remaining_sum > 0; i--) {
        
        // If the cell directly above is true, this element wasn't strictly needed
        if (dp[i - 1][remaining_sum]) {
            continue;
        } 
        // Otherwise, this element MUST have been included
        else {
            ll chosen_num = elements[i - 1];
            chosen_subset.push_back(chosen_num);
            remaining_sum -= chosen_num; 
        }
    }

    reverse(chosen_subset.begin(), chosen_subset.end());

    return {true, chosen_subset};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, target;
    cin >> n >> target;

    vector<ll> elements(n);
    for (ll i = 0; i < n; i++) {
        cin >> elements[i];
    }

    pair<bool, vector<ll>> result = subset_sum(elements, target);
    bool is_possible = result.first;
    vector<ll> subset = result.second;

    if (!is_possible) {
        cout << "No subset adds up to " << target << "\n";
    } else {
        cout << "Target " << target << " is achievable!\n";
        cout << "Elements used: ";
        for (ll i = 0; i < subset.size(); i++) {
            if (i > 0) cout << " + ";
            cout << subset[i];
        }
        cout << " = " << target << "\n";
    }

    return 0;
}