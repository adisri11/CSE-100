#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

// First DFS to compute finish times
void DFS(vector<int>* G, bool* seen, int* f, int v, int& time) {
    seen[v] = true;
    
    // Visit all adjacent vertices
    for (int u : G[v]) {
        if (!seen[u]) {
            DFS(G, seen, f, u, time);
        }
    }
    
    // Assign finish time after all adjacent vertices are processed
    f[v] = time++;
}

// Second DFS to collect vertices in the same SCC
void DFS2(vector<int>* G, bool* seen, vector<int>& scc, int v) {
    seen[v] = true;
    scc.push_back(v);
    
    // Visit all adjacent vertices
    for (int u : G[v]) {
        if (!seen[u]) {
            DFS2(G, seen, scc, u);
        }
    }
}

// Helper function to perform argsort (sorts indices based on array values)
vector<int> argsort(int* arr, int n, bool reverse = true) {
    vector<pair<int, int>> pairs(n);
    for (int i = 0; i < n; i++) {
        pairs[i] = {arr[i], i};
    }
    
    if (reverse) {
        sort(pairs.begin(), pairs.end(), greater<pair<int, int>>());
    } else {
        sort(pairs.begin(), pairs.end());
    }
    
    vector<int> result(n);
    for (int i = 0; i < n; i++) {
        result[i] = pairs[i].second;
    }
    
    return result;
}

int min(vector<int> scc){
  int mini = scc[0];

  for(int i = 0; i < scc.size(); i++){
    if(mini > scc[i]){
      mini = scc[i];
    }
  }

  return mini;
}

int main() {
    int V; // no. of vertices
    int E; // no. of edges
    cin >> V;
    cin >> E;
    
    // Create original graph
    vector<int>* G = new vector<int>[V];
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
    }
    
    // Create transpose graph
    vector<int>* GT = new vector<int>[V];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < G[i].size(); j++) {
            int u = i;
            int v = G[i][j];
            GT[v].push_back(u);
        }
    }
    
    // First DFS to compute finish times
    bool* seen = new bool[V]();  // Initialize all to false
    int* f = new int[V]();
    int time = 0;
    
    for (int i = 0; i < V; i++) {
        if (!seen[i]) {
            DFS(G, seen, f, i, time);
        }
    }
    
    // Sort vertices by finish time (decreasing order)
    vector<int> af = argsort(f, V);
    
    // Reset seen array for second DFS
    delete[] seen;
    seen = new bool[V]();
    
    // Second DFS to find SCCs
    int* res = new int[V];
    
    for (int i = 0; i < V; i++) {
        int v = af[i];
        if (!seen[v]) {
            vector<int> scc;
            DFS2(GT, seen, scc, v);  // Use transpose graph for second DFS
            
            // Find minimum vertex in the SCC
            int sccid = min(scc);
            
            // Assign SCC ID to all vertices in the component
            for (int u : scc) {
                res[u] = sccid;
            }
        }
    }
    
    // Output results
    for (int i = 0; i < V; i++) {
        cout << res[i] << endl;
    }
    
    // Free allocated memory
    delete[] G;
    delete[] GT;
    delete[] seen;
    delete[] f;
    delete[] res;
    
    return 0;
}