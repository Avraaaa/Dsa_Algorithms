#include <bits/stdc++.h>

using namespace std;

#define ll long long
const ll INF = 1e18;

pair<bool, vector<ll>> bfs(vector<vector<ll>> &g, vector<vector<ll>> &capacity, ll starting_node, ll target_node)
{

    ll n = g.size();
    vector<ll> parent(n, -1);
    vector<bool> visited(n, false);

    // EDMONDS-KARP DIFFERENCE: We use a queue instead of a stack
    queue<ll> q;

    //------------pushing the source vertex--------------
    q.push(starting_node);
    visited[starting_node] = true;
    //---------------------------------------------------

    while (!q.empty())
    {

        ll current_node = q.front();
        q.pop();

        for (auto &nxt : g[current_node])
        {

            //------------------- residual capacity check -----------------------------
            // If the adjacent node isn't visited and there is remaining capacity
            if (!visited[nxt] && capacity[current_node][nxt] > 0)
            {
                q.push(nxt);
                visited[nxt] = true;
                parent[nxt] = current_node;

                // If we reached the target node, we found the SHORTEST augmenting path
                if (nxt == target_node)
                {
                    return {true, parent};
                }
            }
            //...........................................................
        }
    }

    return {false, parent};
}

ll edmonds_karp(vector<vector<ll>> &g, vector<vector<ll>> &capacity, ll starting_node, ll target_node)
{

    ll max_flow = 0;

    while (true)
    {

        //-----------------------------finding shortest augmenting path via BFS--------------------------------------
        pair<bool, vector<ll>> bfs_result = bfs(g, capacity, starting_node, target_node);
        bool path_exists = bfs_result.first;
        vector<ll> parent = bfs_result.second;

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

        //-----------------------------updating residual capacities--------------------------------------
        current_node = target_node;

        while (current_node != starting_node)
        {
            ll prev_node = parent[current_node];

            // Subtract from forward edge, add to reverse edge
            capacity[prev_node][current_node] -= path_flow;
            capacity[current_node][prev_node] += path_flow;

            current_node = prev_node;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main()
{

    ll nodes, edges;
    cin >> nodes >> edges;

    vector<vector<ll>> graph(nodes);
    vector<vector<ll>> capacity(nodes, vector<ll>(nodes, 0));

    for (int i = 0; i < edges; i++)
    {
        ll node1, node2, cap;
        cin >> node1 >> node2 >> cap;

        // Adding to adjacency list for fast O(E) traversal
        graph[node1].push_back(node2);

        // IMPORTANT: Must add reverse edge to graph so BFS can traverse
        // backwards during residual capacity updates
        graph[node2].push_back(node1);

        // Storing capacities in a 2D matrix (use += to handle multi-edges safely)
        capacity[node1][node2] += cap;
    }
    ll starting_node;
    cin >> starting_node;
    ll target_node;
    cin >> target_node;
    ll max_flow = edmonds_karp(graph, capacity, starting_node, target_node);

    cout << "Maximum possible flow is: " << max_flow << endl;
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
