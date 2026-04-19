#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF=1e18;


pair<bool,vector<ll>> spfa(vector<vector<ll>> &g, vector<vector<ll>> &capacity, vector<vector<ll>> &cost, ll starting_node, ll target_node){

    ll n = g.size();
    vector<ll>parent(n,-1);
    
    // Instead of just 'visited', we need to track the minimum cost (distance) to each node
    vector<ll>dist(n, INF);
    
    // SPFA requires knowing if a node is currently in the queue to avoid duplicate processing
    vector<bool>in_queue(n,false);
    
    queue<ll> q;

//------------pushing the source vertex--------------
    dist[starting_node] = 0;
    q.push(starting_node);
    in_queue[starting_node] = true;
//---------------------------------------------------


    while(!q.empty()){

        ll current_node = q.front();
        q.pop();
        in_queue[current_node] = false;

        for(auto &nxt : g[current_node]){

//------------------- relaxation with capacity check -----------------------------
            // If there is residual capacity AND the new cost is cheaper than the known cost
            if(capacity[current_node][nxt] > 0 && dist[nxt] > dist[current_node] + cost[current_node][nxt]){
                
                dist[nxt] = dist[current_node] + cost[current_node][nxt];
                parent[nxt] = current_node;
                
                // Only push to queue if it's not already waiting to be processed
                if(!in_queue[nxt]){
                    q.push(nxt);
                    in_queue[nxt] = true;
                }
            }
//...........................................................
        }
    }

    // If dist to target is no longer INF, we found a valid path
    return {dist[target_node] != INF, parent};
}


pair<ll, ll> mcmf(vector<vector<ll>> &g, vector<vector<ll>> &capacity, vector<vector<ll>> &cost, ll starting_node, ll target_node){

    ll max_flow = 0;
    ll min_cost = 0;

    while(true){

//-----------------------------finding CHEAPEST augmenting path via SPFA--------------------------------------
        pair<bool,vector<ll>> spfa_result = spfa(g, capacity, cost, starting_node, target_node);
        bool path_exists = spfa_result.first;
        vector<ll> parent = spfa_result.second;

        if(!path_exists) {
            break; // No more paths with available capacity exist
        }

//-----------------------------finding bottleneck capacity--------------------------------------
        ll path_flow = INF;
        ll current_node = target_node;

        while(current_node != starting_node){
            ll prev_node = parent[current_node];
            path_flow = min(path_flow, capacity[prev_node][current_node]);
            current_node = prev_node;
        }

//-----------------------------updating residual capacities and calculating cost--------------------------------------
        current_node = target_node;

        while(current_node != starting_node){
            ll prev_node = parent[current_node];
            
            // Subtract from forward edge, add to reverse edge
            capacity[prev_node][current_node] -= path_flow;
            capacity[current_node][prev_node] += path_flow;
            
            // Add the cost of this flow to our total minimum cost
            min_cost += path_flow * cost[prev_node][current_node];
            
            current_node = prev_node;
        }

        max_flow += path_flow;
    }

    return {max_flow, min_cost};
}


int main(){

//-----------------------------inputting graph, starting and target node--------------------------------------
    ll nodes,edges;
    cin>>nodes>>edges;

    vector<vector<ll>> graph(nodes);
    vector<vector<ll>> capacity(nodes, vector<ll>(nodes, 0));
    
    // NEW: Cost matrix to track the price per unit of flow
    vector<vector<ll>> cost(nodes, vector<ll>(nodes, 0));

    for(int i=0;i<edges;i++){
        ll u, v, cap, edge_cost;
        cin >> u >> v >> cap >> edge_cost;

        graph[u].push_back(v);
        graph[v].push_back(u); 
        
        capacity[u][v] += cap;
        
        // IMPORTANT: The cost of sending flow forward is positive.
        // The cost of the reverse edge is NEGATIVE. This allows us to "refund" 
        // the cost if the algorithm decides to undo this flow later.
        cost[u][v] = edge_cost;
        cost[v][u] = -edge_cost; 
    }

    ll starting_node;
    cin>>starting_node;
    ll target_node;
    cin>>target_node;

//-----------------------------calculating and printing Max Flow & Min Cost-----------------------------
    pair<ll, ll> result = mcmf(graph, capacity, cost, starting_node, target_node);

    cout << "Maximum possible flow is: " << result.first << endl;
    cout << "Minimum cost for this flow is: " << result.second << endl;

    return 0;
}

/* =========================================
SAMPLE INPUT 
4 nodes, 5 edges
Format: u v capacity cost
=========================================
4 5
0 1 2 1
0 2 1 2
1 2 1 1
1 3 1 3
2 3 2 1
0
3

=========================================
EXPECTED OUTPUT:
=========================================
Maximum possible flow is: 2
Minimum cost for this flow is: 6
=========================================
*/