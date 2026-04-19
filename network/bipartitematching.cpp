#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF=1e18;

//---------------------------------------------------------------------------------------
// The exact same BFS and Edmonds-Karp functions from the previous example!
//---------------------------------------------------------------------------------------

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

//---------------------------------------------------------------------------------------

int main(){

//----------------------------- 1. Input Mapping --------------------------------------
    ll num_applicants, num_jobs, num_edges;
    cin >> num_applicants >> num_jobs >> num_edges;

    // Total nodes = Super Source (1) + Applicants + Jobs + Super Sink (1)
    ll total_nodes = num_applicants + num_jobs + 2;
    ll starting_node = 0; 
    ll target_node = total_nodes - 1;

    vector<vector<ll>> graph(total_nodes);
    vector<vector<ll>> capacity(total_nodes, vector<ll>(total_nodes, 0));

//----------------------------- 2. Graph Construction ---------------------------------
    // Step A: Connect Super Source to all Applicants (Nodes 1 to num_applicants)
    for(int i = 1; i <= num_applicants; i++){
        graph[starting_node].push_back(i);
        graph[i].push_back(starting_node); // Reverse edge
        capacity[starting_node][i] = 1;
    }

    // Step B: Connect all Jobs to Super Sink (Nodes num_applicants+1 to num_applicants+num_jobs)
    for(int j = 1; j <= num_jobs; j++){
        ll job_node = num_applicants + j;
        graph[job_node].push_back(target_node);
        graph[target_node].push_back(job_node); // Reverse edge
        capacity[job_node][target_node] = 1;
    }

    // Step C: Connect Applicants to Jobs based on input
    for(int i = 0; i < num_edges; i++){
        ll applicant, job;
        cin >> applicant >> job; // Assuming 1-indexed input (e.g., App 1 wants Job 1)
        
        // Shift job index to avoid overlapping with applicant nodes
        ll job_node = num_applicants + job; 

        graph[applicant].push_back(job_node);
        graph[job_node].push_back(applicant); // Reverse edge
        capacity[applicant][job_node] = 1;
    }

//----------------------------- 3. Calculate Maximum Matches --------------------------
    ll max_matches = edmonds_karp(graph, capacity, starting_node, target_node);
    cout << "Maximum number of applicants matched: " << max_matches << endl;

//----------------------------- 4. Print Who Got Which Job ----------------------------
    cout << "\nMatching Details:" << endl;
    for(int i = 1; i <= num_applicants; i++){
        for(int j = 1; j <= num_jobs; j++){
            ll job_node = num_applicants + j;
            
            // If the original capacity was 1, but is now 0, it means flow successfully 
            // traveled from the applicant to this job!
            bool was_an_option = false;
            for(auto &neighbor : graph[i]){
                if(neighbor == job_node) was_an_option = true;
            }

            if(was_an_option && capacity[i][job_node] == 0){
                cout << "Applicant " << i << " was assigned to Job " << j << endl;
            }
        }
    }

    return 0;
}

/* =========================================
SAMPLE INPUT 
(4 Applicants, 4 Jobs, 6 preferences)
Applicant 1 wants Job 1 and 2
Applicant 2 wants Job 1
Applicant 3 wants Job 2 and 3
Applicant 4 wants Job 3
=========================================
4 4 6
1 1
1 2
2 1
3 2
3 3
4 3

=========================================
EXPECTED OUTPUT:
=========================================
Maximum number of applicants matched: 3

Matching Details:
Applicant 1 was assigned to Job 2
Applicant 2 was assigned to Job 1
Applicant 4 was assigned to Job 3
=========================================
*/