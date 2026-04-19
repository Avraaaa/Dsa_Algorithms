#include <bits/stdc++.h>
using namespace std;

#define ll long long



ll dfsUtil(ll node, vector<vector<ll>> &adj, vector<ll> &dp) {
    
    if (dp[node] != -1) {
        return dp[node];
    }
    
    ll maxi = 0;
    

    int size = adj[node].size();
    for (int i=size-1; i>=0; i--) {
        int v = adj[node][i];
        maxi = max(maxi, 1 + dfsUtil(v, adj, dp));
    }
    
    dp[node] = maxi;
    return dp[node];
}

ll dfs(vector<vector<ll>>& adj) {
    ll n = adj.size()-1;
    
    vector<ll> dp(n,-1);
    ll maxi = 0;
    for (ll i=1; i<=n; i++) {
        maxi = max(maxi,dfsUtil(i, adj, dp));
    }
    return maxi;
}


int main(){
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> adj(n+1);

    for(ll i = 1; i <= m; i++){
        ll u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }


    cout <<dfs(adj)<<endl;
}