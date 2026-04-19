#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<ll> bfs(vector<vector<ll>>& adj){
    ll n = adj.size();
    vector<ll> visited(n,0), res;
    queue<ll> q;

    q.push(0);
    visited[0] = 1;

    while(!q.empty()){
        ll node = q.front();
        q.pop();

        res.push_back(node);

        for(ll i = 0; i < adj[node].size(); i++){
            ll v = adj[node][i];
            if(!visited[v]){
                visited[v] = 1;
                q.push(v);
            }
        }
    }
    return res;
}

int main(){
    ll n, m;
    cin >> n >> m;

    vector<vector<ll>> adj(n);

    for(ll i = 0; i < m; i++){
        ll u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    vector<ll> res = bfs(adj);

    for(auto x : res) cout << x << " ";
    cout << endl;
}