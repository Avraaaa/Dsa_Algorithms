#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<vector<ll>> dp01;

ll knapsack01(ll W, vector<vector<ll>>& a) {
    ll n = a.size();
    vector<vector<ll>> dp01(n + 1, vector<ll>(W + 1, 0));

    for (ll i = 1; i <= n; i++) {
        ll val = a[i - 1][0];
        ll wt = a[i - 1][1];

        for (ll w = 0; w <= W; w++) {
            dp01[i][w] = dp01[i - 1][w];
            if (w >= wt)
                dp01[i][w] = max(dp01[i][w], dp01[i - 1][w - wt] + val);
        }
    }
    return dp01[n][W];
}

vector<ll> traceback01(ll W, vector<vector<ll>>& a) {
    ll n = a.size();
    vector<ll> chosen;

    ll i = n, w = W;
    while (i > 0 && w > 0) {
        if (dp01[i][w] != dp01[i - 1][w]) {
            chosen.push_back(i - 1);
            w -= a[i - 1][1];
        }
        i--;
    }

    reverse(chosen.begin(), chosen.end());
    return chosen;
}

ll knapsackUnbounded(ll W, vector<vector<ll>>& a) {
    vector<ll> dp(W + 1, 0);

    for (ll i = 0; i < a.size(); i++) {
        ll val = a[i][0];
        ll wt = a[i][1];

        for (ll w = wt; w <= W; w++) {
            dp[w] = max(dp[w], dp[w - wt] + val);
        }
    }
    return dp[W];
}

void solve() {
    ll n;
    cin >> n;

    vector<vector<ll>> a(n, vector<ll>(2));
    for (ll i = 0; i < n; i++) cin >> a[i][0];
    for (ll i = 0; i < n; i++) cin >> a[i][1];

    ll W;
    cin >> W;

    ll best01 = knapsack01(W, a);
    vector<ll> items01 = traceback01(W, a);
    ll bestUnbounded = knapsackUnbounded(W, a);

    cout << best01 << "\n";
    for (ll i : items01) cout << i << " ";
    cout << "\n";
    cout << bestUnbounded;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    solve();
}
