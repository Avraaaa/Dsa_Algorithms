#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

// Adapted Bellman-Ford to find the cheapest path with available capacity
pair<bool, vector<ll>> bellman_ford(vector<vector<ll>> &g, vector<vector<ll>> &capacity, vector<vector<ll>> &cost, ll starting_node, ll target_node)
{
    ll n = g.size();

    vector<ll> distance_from_source(n, INF);
    vector<ll> parent(n, -1);

    distance_from_source[starting_node] = 0;

    //------------------- Phase 1: Relax edges V-1 times -----------------------------
    // first v-1 times of the loop = relaxation
    // the nth i loop, if a shorter path is found, that means negative cycle exists->infinitely reduces distance;
    for (int i = 1; i <= n; i++)
    {
        // loop through every node;
        for (int u = 0; u < n; u++)
        {
            // if we havent reached node u yet, we cant use it to reach other nodes
            if (distance_from_source[u] == INF)
                continue;

            // Looking up all the neighbors v of u
            for (auto &v : g[u])
            {
                // CRITICAL FLOW MODIFICATION: Only consider edges with residual capacity > 0
                if (capacity[u][v] > 0 && distance_from_source[v] > distance_from_source[u] + cost[u][v])
                {
                    if (i == n)
                    {
                        cout << "\n[WARNING] Graph contains a negative weight cycle!" << endl;
                        // Return false because we cannot safely find a shortest path
                        return {false, parent};
                    }
                    else
                    {
                        distance_from_source[v] = distance_from_source[u] + cost[u][v];
                        parent[v] = u;
                    }
                }
            }
        }
    }

    // Return true if we successfully found a path to the target
    return {distance_from_source[target_node] != INF, parent};
}

pair<ll, ll> mcmf(vector<vector<ll>> &g, vector<vector<ll>> &capacity, vector<vector<ll>> &cost, ll starting_node, ll target_node)
{
    ll max_flow = 0;
    ll min_cost = 0;

    while (true)
    {
        //-----------------------------finding CHEAPEST augmenting path via Bellman-Ford--------------------------------------
        pair<bool, vector<ll>> bf_result = bellman_ford(g, capacity, cost, starting_node, target_node);
        bool path_exists = bf_result.first;
        vector<ll> parent = bf_result.second;

        if (!path_exists)
        {
            break; // No more paths with available capacity exist
        }

        //-----------------------------finding bottleneck capacity--------------------------------------
        ll path_flow = INF;
        ll current_node = target_node;

        while (current_node != starting_node)
        {
            ll prev_node = parent[current_node];
            path_flow = min(path_flow, capacity[prev_node][current_node]);
            current_node = prev_node;
        }

        //-----------------------------updating residual capacities and calculating cost--------------------------------------
        current_node = target_node;

        while (current_node != starting_node)
        {
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

int main()
{
    //-----------------------------inputting graph, starting and target node--------------------------------------
    ll nodes, edges;
    cin >> nodes >> edges;

    vector<vector<ll>> graph(nodes);
    vector<vector<ll>> capacity(nodes, vector<ll>(nodes, 0));
    vector<vector<ll>> cost(nodes, vector<ll>(nodes, 0));

    for (int i = 0; i < edges; i++)
    {
        ll u, v, cap, edge_cost;
        cin >> u >> v >> cap >> edge_cost;

        // Forward edge
        graph[u].push_back(v);
        // Reverse edge required for flow undo mechanics
        graph[v].push_back(u);

        capacity[u][v] += cap;

        // Cost of forward edge is positive, cost of reverse edge is negative (refund)
        cost[u][v] = edge_cost;
        cost[v][u] = -edge_cost;
    }

    ll starting_node;
    cin >> starting_node;
    ll target_node;
    cin >> target_node;

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