#include <bits/stdc++.h>
using namespace std;

#define ll long long

int knapsack(ll W, vector<vector<ll>>& a) {
    vector<ll> dp(W + 1, 0);

    for (ll i = 0; i < a.size(); i++) {
        for (ll j = W; j >= a[i][1]; j--) {
            dp[j] = max(dp[j], dp[j - a[i][1]] + a[i][0]);
        }
    }
    return dp[W];
}

void solve(){
    ll n;
    cin >> n;

    vector<vector<ll>> a(n, vector<ll>(2));

    for (ll i = 0; i < n; i++) {
        cin >> a[i][0];   
    }
    for (ll i = 0; i < n; i++) {
        cin >> a[i][1];   
    }

    ll W;
    cin >> W;

    ll result = knapsack(W, a);
    cout << result;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    solve();
}
