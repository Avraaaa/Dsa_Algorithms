#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<ll> dfs(vector<vector<ll>>& adj){
    ll n = adj.size();
    vector<ll> visited(n,0), res;
    stack<ll> st;
    st.push(0);


    ///in dfs we use stack and mark when pop from stack
    //in bfs we use queue and mark when push
    while(!st.empty()){
        ll node = st.top();
        st.pop();

        if(visited[node]) continue;

        visited[node] = 1;
        res.push_back(node);

        for(ll i = adj[node].size() - 1; i >= 0; i--){
            ll v = adj[node][i];
            if(!visited[v]) st.push(v);
        }
    }
    return res;
}

//this is only when unconnected graph

/*
void dfsUtil(int s, vector<vector<int>> &adj, vector<bool> &visited, 
vector<int> &res) {
    
    stack<int> st;
    st.push(s);
    
    while (!st.empty()) {
        int node = st.top();
        st.pop();
        
        // If node is already visited, continue
        if (visited[node] == true) {
            continue;
        }
        
        // Mark this node as visited 
        visited[node] = true;
        res.push_back(node);
        
        // Traverse all edges (as stack is used, so 
        // push from right to left)
        int size = adj[node].size();
        for (int i=size-1; i>=0; i--) {
            int v = adj[node][i];
            if (!visited[v]) st.push(v);
        }
    }
}

vector<int> dfs(vector<vector<int>>& adj) {
    int n = adj.size();
    
    vector<bool> visited(n, false);
    vector<int> res;
    
    for (int i=0; i<n; i++) {
        if (!visited[i]) {
            dfsUtil(i, adj, visited, res);
        }
    }
    
    return res;
}
*/

int main(){
    ll n, m;
    cin >> n >> m;
    //adjacency list
    vector<vector<ll>> adj(n);

    for(ll i = 0; i < m; i++){
        ll u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    vector<ll> res = dfs(adj);

    for(auto x : res) cout << x << " ";
    cout << endl;
}

