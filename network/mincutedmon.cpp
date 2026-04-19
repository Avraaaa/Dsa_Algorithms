#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int INF = 1e18;

pair<bool,vector<ll>> bfs(vector<vector<ll>> &g, vector<vector<ll>> &capacity, ll starting_node, ll target_node){
    ll n = g.size();
    vector<ll>parent(n,-1);
    vector<bool>visited(n,false);
    queue<ll> q;

    q.push(starting_node);
    visited[starting_node]=true;

    while(!q.empty()){
        ll current_node = q.front();
        q.pop();

        for(auto &nxt : g[current_node]){
            if(!visited[nxt] && capacity[current_node][nxt] > 0){
                q.push(nxt);
                visited[nxt]=true;
                parent[nxt]=current_node;
                if(nxt == target_node){
                    return {true,parent};
                }
            }
        }
    }
    return {false,parent};
}


ll edmonds_karp(vector<vector<ll>> &g, vector<vector<ll>> &capacity, ll starting_node, ll target_node){
    ll max_flow = 0;

    while(true){
        pair<bool,vector<ll>> bfs_result = bfs(g, capacity, starting_node, target_node);
        bool path_exists = bfs_result.first;
        vector<ll> parent = bfs_result.second;

        if(!path_exists) break; 

        ll path_flow = INF;
        ll current_node = target_node;

        while(current_node != starting_node){
            ll prev_node = parent[current_node];
            path_flow = min(path_flow, capacity[prev_node][current_node]);
            current_node = prev_node;
        }

        current_node = target_node;
        while(current_node != starting_node){
            ll prev_node = parent[current_node];
            capacity[prev_node][current_node] -= path_flow;
            capacity[current_node][prev_node] += path_flow;
            current_node = prev_node;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

//Only change from edmonds karp is this new algorithm


vector<bool> get_reachable_nodes(vector<vector<ll>> &g, vector<vector<ll>> &capacity, ll starting_node){

    ll n = g.size();
    vector<bool> visited(n,false);
    queue<ll> q;
    q.push(starting_node);
    visited[starting_node] = true;

    while(!q.empty()){
        ll current_node = q.front();
        q.pop();

        for(auto &nxt:g[current_node]){
            if(!visited[nxt]&& capacity[current_node][nxt]>0){
                q.push(nxt);
                visited[nxt] = true;
            }
        }
    }
    return visited;

}

int main(){
    ll nodes,edges;
    cin>>nodes>>edges;

    vector<vector<ll>> graph(nodes);
    vector<vector<ll>> capacity(nodes, vector<ll>(nodes, 0));
    
    // Storing original edges to verify the min-cut at the end
    vector<pair<ll, ll>> original_edges;

    for(int i=0;i<edges;i++){
        ll node1,node2,cap;
        cin>>node1>>node2>>cap;

        original_edges.push_back({node1, node2});

        graph[node1].push_back(node2);
        graph[node2].push_back(node1); 
        capacity[node1][node2] += cap;
    }

    ll starting_node;
    cin>>starting_node;
    ll target_node;
    cin>>target_node;

//----------------------------- 1. Calculate Max Flow -----------------------------
    ll max_flow = edmonds_karp(graph, capacity, starting_node, target_node);
    cout<<"Maximum possible flow is: "<<max_flow<<endl;


//----------------------------- 2. Find Reachable Nodes (Set S) -------------------
    vector<bool> reachable_from_source = get_reachable_nodes(graph, capacity, starting_node);


//----------------------------- 3. Print Cut Edges --------------------------------
    cout << "Edges in the Minimum Cut are:" << endl;
    for (auto &edge : original_edges) {
        ll u = edge.first;
        ll v = edge.second;

        // If 'u' is reachable but 'v' is completely blocked off
        if (reachable_from_source[u] == true && reachable_from_source[v] == false) {
            cout << u << " -> " << v << endl;
        }
    }

    return 0;
}

// 6 10
// 0 1 16
// 0 2 13
// 1 2 10
// 1 3 12
// 2 1 4
// 2 4 14
// 3 2 9
// 3 5 20
// 4 3 7
// 4 5 4
// 0
// 5