#include <bits/stdc++.h>

using namespace std;

#define ll long long
const ll INF = 1e18;

pair<vector<vector<ll>>, vector<vector<ll>>> floyd_warshall(vector<vector<ll>> &dist, ll n)
{

    vector<vector<ll>> next_node(n, vector<ll>(n, -1));

    // next_node[i][j] stores the first step, for going from i to j

    // routing table based on directed edges, as floyd warshall doesnt really care whether the graphs directed or undirected
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] != INF && i != j)
            {
                next_node[i][j] = j;
            }
        }
    }

    //------------------- Phase 1: Triple Nested Loop (The Core) -----------------------------
    // 'k' is the intermediate routing node. The order of these loops is CRITICAL.

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] < INF && dist[k][j] < INF)
                {
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];

                        next_node[i][j] = next_node[i][k];
                    }
                }
            }
        }
    }

    //------------------- Phase 2: Check for Negative Cycles -----------------------------
    // In Floyd-Warshall, a negative cycle means the distance from a node to ITSELF
    // drops below 0.
    for (int i = 0; i < n; i++)
    {
        if (dist[i][i] < 0)
        {
            cout << "\n[WARNING] Graph contains a negative weight cycle!" << endl;
            return {{}, {}};
        }
    }

    return {dist, next_node};
}

vector<ll> get_path(vector<vector<ll>> &next_node, ll start, ll target)
{
    vector<ll> path;

    // If there's no valid first step, the path doesn't exist
    if (next_node[start][target] == -1) return path;

    path.push_back(start);
    
    //unlike dijkstra in floyid warshall we walk forward, using the 2d routing table until we hit hte taqrget
    while (start != target) {
        start = next_node[start][target];
        path.push_back(start);
    }

    return path;
}

int main()
{

    ll nodes, edges;

    cin >> nodes >> edges;

    // NxN matrix filled with INF
    vector<vector<ll>> graph(nodes, vector<ll>(nodes, INF));

    for (int i = 0; i < nodes; i++)
    {
        graph[i][i] = 0;
    }

    for (int i = 0; i < edges; i++)
    {
        ll u, v, weight;
        cin >> u >> v >> weight;

        // tis for undirected graph
        // min() in case the input has multiple edges between same two nodes
        graph[u][v] = min(graph[u][v], weight);
        graph[v][u] = min(graph[v][u], weight);
    }

    ll starting_node;
    cin >> starting_node;
    ll target_node;
    cin >> target_node;

    pair<vector<vector<ll>>, vector<vector<ll>>> result = floyd_warshall(graph, nodes);

    if (result.first.empty())
    {
        return 0;
    }

    vector<vector<ll>> all_pairs_shortest_paths = result.first;
    vector<vector<ll>> next_nodes = result.second;

    cout << "\nAll-Pairs Shortest Path Matrix:" << endl;
    for (int i = 0; i < nodes; i++)
    {
        for (int j = 0; j < nodes; j++)
        {
            if (all_pairs_shortest_paths[i][j] == INF)
                cout << "INF\t";
            else
                cout << all_pairs_shortest_paths[i][j] << "\t";
        }
        cout << endl;
    }

    //--------------------------------- Path Printing -------------------------------------------------------
    if (starting_node < 0 || starting_node >= nodes || target_node < 0 || target_node >= nodes)
    {
        cout << "\ninvalid nodes" << endl;
    }
    else if (all_pairs_shortest_paths[starting_node][target_node] == INF)
    {
        cout << "\nno path exists" << endl;
    }
    else
    {
        vector<ll> path = get_path(next_nodes, starting_node, target_node);
        cout << "\nshortest path for the desired node is (Distance: "
             << all_pairs_shortest_paths[starting_node][target_node] << "):" << endl;

        for (int i = 0; i < path.size(); i++)
        {
            if (i)
                cout << " -> ";
            cout << path[i];
        }
        cout << endl;
    }

    return 0;
}

// 5 6
// 0 1 4
// 0 3 5
// 1 2 1
// 1 4 6
// 2 3 3
// 3 4 2
// 0
// 2