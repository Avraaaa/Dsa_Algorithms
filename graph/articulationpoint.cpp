#include<bits/stdc++.h>
using namespace std;

// Global timer for discovery times
int timer = 1;

void dfs(vector<vector<int>>& graph, vector<int>& v, vector<int>& disc, vector<int>& low, set<int>& articulation_points, int node, int parent){
    // Mark visited and assign discovery and low times
    v[node] = 1;
    disc[node] = low[node] = timer;
    timer++;
    
    int children = 0; // Count independent children for the root rule

    for(int nxt : graph[node]){
        // Skip the immediate parent to prevent false back-edges
        if(nxt == parent){
            continue;
        }

        if(!v[nxt]){
            children++;
            
            // Go deep into the child node
            dfs(graph, v, disc, low, articulation_points, nxt, node);
            
            // BACKTRACKING: Once the child finishes, update the current node's low
            // If the child found a back-edge higher up, the parent inherits it
            low[node] = min(low[node], low[nxt]);
            
            // RULE 1: Non-root node check
            // If the child's lowest reachable node is below or exactly at the current node,
            // the current node is an articulation point.
            if(parent != -1 && low[nxt] >= disc[node]){
                articulation_points.insert(node);
            }
        }
        else{
            // BACK-EDGE FOUND: Update low to the discovered time of the ancestor
            low[node] = min(low[node], disc[nxt]);
        }
    }
    
    // RULE 2: Root node check
    // If we are at the root and it has more than 1 independent branch
    if(parent == -1 && children > 1){
        articulation_points.insert(node);
    }
}

int main(){
    int vertices, edges;

    cout << "Enter num of vertices : ";
    cin >> vertices;
    cout << endl;

    cout << "Enter num of edges: ";
    cin >> edges;
    cout << endl;

    vector<vector<int>> graph(vertices);

    cout << "enter the edges :" << endl;

    for(int i = 0; i < edges; i++){
        int a, b;
        cin >> a >> b;

        if(a >= vertices || b >= vertices || a < 0 || b < 0){
            cout << "Invalid entry" << endl;
            continue;
        } 

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int start;
    cout << "Starting edge (root) : ";
    cin >> start;
    cout << endl;

    vector<int> visited(vertices, 0);
    vector<int> disc(vertices, -1);
    vector<int> low(vertices, -1);
    
    // Using a set to avoid printing duplicates if a node is flagged multiple times
    set<int> articulation_points; 

    // Initial call passes -1 since the starting node has no parent
    dfs(graph, visited, disc, low, articulation_points, start, -1);

    cout << "\nArticulation Points:" << endl;
    if(articulation_points.empty()){
        cout << "None" << endl;
    } else {
        for(int ap : articulation_points){
            cout << "Node " << ap << endl;
        }
    }

    return 0;
}