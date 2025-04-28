#include <iostream>
#include <vector>
#include <climits>
#include <algorithm> 
using namespace std;

int main(){

  int V; // no. of vertices
  int E; // no. of edges
  cin>>V;
  cin>>E;

  int** W = new int*[V];
  for(int i = 0; i < V; i++){
    W[i] = new int[V];
    for(int j = 0; j < V; j++){
      W[i][j] = INT_MAX;
    }
  }

  vector<int>* G = new vector<int>[V];
  for(int i = 0; i < E; i++){
    int u,v,w;
    cin>>u>>v>>w;
    W[u][v] = w;
    W[v][u] = w;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  
  vector<int> Q(V);
  vector<bool> value(V, false);
  int start = 0;
  int* parents = new int[V];
  int* keys = new int[V];
  for(int i = 0; i < V; i++){
    parents[i] = -1;
    keys[i] = INT_MAX;
    Q[i] = i;
  }
  keys[start] = 0;

  // set keys[i] to 0
  // put all v into Q

  while(!Q.empty()){
    // find vertex which has min in keys: for loop in Q
    int min = INT_MAX;
    int u = -1;
    int position = -1;

    for(int i = 0; i < Q.size(); i++){
      if(keys[Q[i]] < min){
        min = keys[Q[i]];
        u = Q[i];
        position = i;
      }
    }
    // remove element at index 'u' from Q
    Q.erase(Q.begin() + position);
    value[u] = true;

    for(int v : G[u]){
//    for(int i = 0; i < G[u].size(); i++){
//      int v = G[u][i];
      if(!value[v] && W[u][v] < keys[v]){
        parents[v] = u;
        keys[v] = W[u][v];
      }
    }
  }
  
  // print parents from index 1
  for(int v = 1; v < V; v++){
    cout << parents[v] << "\n";
  }

  return 0;
}















