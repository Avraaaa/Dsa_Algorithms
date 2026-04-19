#include <bits/stdc++.h>

using namespace std;

#define ll long long


//------------------- Step 1: First DFS to get finishing times -----------------------------
void dfs_fill_stack(ll node, vector<vector<ll>> &g, vector<bool> &visited, stack<ll> &st){

    visited[node] = true;

    for(auto &nxt:g[node]){
        if(!visited[nxt]){
            dfs_fill_stack(nxt,g,visited,st);
        }
    }

    //push teh nodes into the stack only when they get finished.

    st.push(node);


}
//------------------- Step 3: Second DFS to collect isolated SCCs --------------------------
void dfs_collect_scc(ll node, vector<vector<ll>> &rev_g, vector<bool> &visited, vector<ll> &current_scc){
 
        visited[node] = true;
        current_scc.push_back(node);

        for(auto &nxt:rev_g[node]){
            if(!visited[nxt]){
                dfs_collect_scc(nxt,rev_g,visited,current_scc);
            }
        }

}

int main(){

    ll nodes, edges;
    cin>>nodes>>edges;

    vector<vector<ll>> graph(nodes);
    vector<vector<ll>> rev_graph(nodes);

    for(int i=0;i<edges;i++){
        ll u,v;
        cin>>u>>v;

        graph[u].push_back(v);
        rev_graph[v].push_back(u);
    }
    //the first dfs pass
    vector<bool> visited(nodes,false);
    stack<ll> st;

    for(ll i=0;i<nodes;i++){
        if(!visited[i]){
            dfs_fill_stack(i,graph,visited,st);
        }
    }

    for(ll i=0;i<nodes;i++){
        visited[i] = false;
    }

    vector<vector<ll>> all_sccs;

    while(!st.empty()){

        ll node = st.top();
        st.pop();

        if(!visited[node]){
            vector<ll> current_scc;
            //This dfs will only be able to reach nodes with its own scc
            dfs_collect_scc(node,rev_graph,visited,current_scc);
            all_sccs.push_back(current_scc);
        }

    }

cout << "\nStrongly Connected Components (SCCs) found: " << all_sccs.size() << endl;
    for(int i = 0; i < all_sccs.size(); i++){
        cout << "SCC " << i + 1 << ": ";
        for(ll node : all_sccs[i]){
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}

/* =========================================
SAMPLE INPUT 
(Based on the graph from the video at 00:01:30)
=========================================
8
9
0 1
1 2
2 0
2 3
3 4
4 5
5 6
6 7
5 4

=========================================
EXPECTED OUTPUT:
=========================================
Strongly Connected Components (SCCs) found: 5
SCC 1: 0 2 1 
SCC 2: 3 
SCC 3: 4 5 
SCC 4: 6 
SCC 5: 7 
=========================================
*/

