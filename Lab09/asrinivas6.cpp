#include <iostream>
#include <vector>
using namespace std;

void DFS(vector<int>* G, bool* seen, int* f, int& time, int v){
  // populate f
  seen[v] = true;

  for(int u : G[v]){
    if(!seen[u]){
      DFS(G, seen, f, time, u);
    }
  }

  f[v] = time++;
  
}

void DFS2(vector<int>* G, bool* seen, vector<int>& scc, int v){
  seen[v] = true;
  scc.push_back(v);

  for(int u : G[v]){
    if(!seen[u]){
      DFS2(G, seen, scc, u);
    }
  }
}


vector<int> argsort(int* f, int V) {
  vector<int> indicies(V);
  vector<int> sorted(V);
  for(int i = 0; i < V; i++){
    sorted[i] = f[i];
  }

  sort(sorted.begin(), sorted.end(), greater<int>());

  for(int i = 0; i < V; i++){
    for(int j = 0; j < V; j++){
      if(sorted[i] == f[j]){
        indicies[i] = j;
      }
    }
  }
  
  return indicies;
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

int main(){

  int V; // no. of vertices
  int E; // no. of edges
  cin>>V;
  cin>>E;

  vector<int>* G = new vector<int>[V];
  for(int i = 0; i < E; i++){
    int u,v;
    cin>>u>>v;
    G[u].push_back(v);
  }

  vector<int>* GT = new vector<int>[V];
  for(int i = 0; i < V; i++){
    for(int j = 0; j < G[i].size(); j++){
      int u = i;
      int v = G[i][j];
      GT[v].push_back(u);
    }
  }

  bool* seen = new bool[V];
  int* f = new int[V];
  int time = 0;
  for(int i = 0; i < V; i++){
    if(!seen[i]){
       DFS(G, seen, f, time, i);
    }
  }
  
  //              0  1  2  3  4
  // argsort f = [3, 9, 4, 2, 5]
  // sort:  [2, 3, 4, 5, 9]
  // asort: [3, 0, 2, 4, 1]
  // modify sorting, you can built-in function to do argsort

  vector<int> af = argsort(f, V);
  delete[] seen;
  seen = new bool[V];
  int* res = new int[V];

  for(int i = 0; i < V; i++){
    int v = af[i];
    if(!seen[v]){
      vector<int> scc;
      DFS2(GT, seen, scc, v);
      int sccid = min(scc);
      for(int u : scc){
         res[u] = sccid;
      }
    }
  }

  for(int i = 0; i < V; i++){
    cout<<res[i]<<endl;
  }

  return 0;
}