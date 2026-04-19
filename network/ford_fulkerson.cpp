#include <bits/stdc++.h>

using namespace std;

#define ll long long
const ll INF = 1e18;


pair<bool,vector<ll>> dfs(vector<vector<ll>> &g, vector<vector<ll>> &capacity, ll starting_node, ll target_node){

    ll n=g.size();
    vector<ll> parent(n,-1);
    vector<bool>visited(n,false);
    stack<ll> st;

    st.push(starting_node);
    visited[starting_node] = true;

    while(!st.empty()){

        ll current_node = st.top();
        st.pop();

        for(auto &nxt :g[current_node]){

            //residual capacity check
            //if the adjacent node isnt visited yet and there is remaining capacity

            if(!visited[nxt] && capacity[current_node][nxt]>0){
                st.push(nxt);
                visited[nxt] = true;
                parent[nxt] = current_node;


                if(nxt==target_node){

                    return{true,parent};

                }
            }

        }

    }

    return{false,parent};
}

ll ford_fulkerson(vector<vector<ll>> &g, vector<vector<ll>> &capacity, ll starting_node,ll target_node){

    ll max_flow = 0;
    while(true){
        //finding augmenting path using dfs
        pair<bool,vector<ll>> dfs_results = dfs(g,capacity,starting_node,target_node);
        bool path_exists = dfs_results.first;
        vector<ll> parent = dfs_results.second;

        if(!path_exists){
            break;
        }

        //finding bottleneck capacity

        ll path_flow = INF;
        ll current_node = target_node;
        while(current_node!=starting_node){
            ll prev_node = parent[current_node];
            path_flow = min(path_flow,capacity[prev_node][current_node]);
            current_node = prev_node;
        }

        //updating residual capacities
        
        current_node = target_node;
        while(current_node!=starting_node){
            ll prev_node = parent[current_node];
            capacity[prev_node][current_node] -=path_flow;
            capacity[current_node][prev_node] +=path_flow;
            current_node = prev_node;
        }
        max_flow+=path_flow;

    }
    return max_flow;

}

int main()
{

    ll nodes, edges;
    cin >> nodes >>edges;

    vector<vector<ll>> graph(nodes);
    vector<vector<ll>> capacity(nodes, vector<ll>(nodes, 0));

    for (int i = 0; i < edges; i++)
    {
        ll node1, node2, cap;
        cin >> node1 >> node2 >> cap;

        graph[node1].push_back(node2);
        // IMPORTANT: Must add reverse edge to graph so DFS can traverse backwards during residual capacity updates
        graph[node2].push_back(node1);
        //+= to handle multi edges
        capacity[node1][node2] += cap;
    }

    ll starting_node;
    cin >> starting_node;
    ll target_node;
    cin >> target_node;

    ll max_flow = ford_fulkerson(graph,capacity,starting_node,target_node);
    cout<<"Maximum possible flow is: "<<max_flow<<endl;

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