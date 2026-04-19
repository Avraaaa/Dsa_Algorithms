#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

pair<vector<ll>, vector<ll>> bellman_ford(vector<vector<pair<ll, ll>>> &g, ll starting_node)
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
        // loop through evey node;
        for (int u = 0; u < n; u++)
        {
            // if we havent reached node u yet, we cant use it to reach other nodes
            if (distance_from_source[u] == INF)
                continue;

            // Looking up all the neighbors v of u

            for (auto &p : g[u])
            {
                ll wt = p.first;
                ll v = p.second;

                if (distance_from_source[v] > distance_from_source[u] + wt)
                {
                    if (i == n)
                    {
                        {
                            cout << "\n[WARNING] Graph contains a negative weight cycle!" << endl;
                            //returning a pair containing two empty vectors
                            return {{},{}};
                        }
                    }
                    else{
                        distance_from_source[v] = distance_from_source[u] + wt;
                        parent[v] = u;
                    }
                }
            }
        }
    }


    return {distance_from_source, parent};
}

vector<ll> get_path(vector<ll> &parent, ll target_node)
{

    vector<ll> path;

    while (target_node != -1)
    {
        path.push_back(target_node);
        target_node = parent[target_node];
    }

    reverse(path.begin(), path.end());
    return path;
}

int main()
{

    //-----------------------------inputting graph,starting and target node--------------------------------------
    ll nodes, edges;
    cin >> nodes >> edges;
    vector<vector<pair<ll, ll>>> graph(nodes);
    for (int i = 0; i < edges; i++)
    {
        ll node1, node2, weight;
        cin >> node1 >> node2 >> weight;
        graph[node1].push_back({weight, node2});
        //This makes the graph an undirected graph, for directed graph, just comment it out
        //Note: Bellman ford graph if it has negative edge will always have a negative weight cycle for undirected graph
        graph[node2].push_back({weight, node1});
    }

    ll starting_node;
    cin >> starting_node;
    ll target_node;
    cin >> target_node;

    //-----------------------------receiving the pair of vectors and seperating the shortest path and parents vector-------------

    pair<vector<ll>, vector<ll>> distance_and_parent;
    distance_and_parent = bellman_ford(graph, starting_node);

    //check if the vector is empty(negative weight cycle was found)

    if(distance_and_parent.first.empty()){
        return 0;
    }

    vector<ll> shortest_paths = distance_and_parent.first;
    vector<ll> parents = distance_and_parent.second;

    for (int i = 0; i < nodes; i++)
    {
        cout << i << " : " << shortest_paths[i] << endl;
    }

    //---------------------------------path printing-------------------------------------------------------
    vector<ll> path;
    if (target_node < 0 || target_node >= nodes)
    {
        cout << "invalid target node" << endl;
    }
    else if (shortest_paths[target_node] == INF)
    {
        cout << "no path exists" << endl;
    }
    else
    {
        path = get_path(parents, target_node);
        cout << "shortest path for the desired node is" << endl;
    }
    for (int i = 0; i < path.size(); i++)
    {
        if (i)
            cout << " -> ";
        cout << path[i];
    }

    cout << endl;
}

// 7 12
// 0 1 2
// 0 3 1
// 1 3 3
// 1 4 10
// 2 0 4
// 2 5 5
// 3 2 2
// 3 5 8
// 3 6 3
// 3 4 2
// 4 6 6
// 6 5 1
// 0
// 6
