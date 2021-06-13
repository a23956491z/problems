#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <queue>

using namespace std;
class Edge;

class Edge{
public:
  int from, to;
  double flow;
  double capacity;
  Edge *residual;

  Edge(int f, int t, double c){
    from = f;
    to = t;
    capacity = c;
    flow = 0;
  }

  bool isResidual(){
    return capacity == 0;
  }

  double remainingCapacity(){
    return capacity - flow;
  }

  void augment(double bottleNeck){
    if(residual == nullptr){
      printf("NULLPTR!!\n");
      return;
    }
    flow += bottleNeck;
    residual->flow -= bottleNeck;
    //printf("augment | %2d -> %2d | flow: %7.1lf\n", from, to, flow);
  }

  string toString(int s, int t){
    string u((from == s)? "s" : ((from == t)? "t" : to_string(from)));
    string v((to == s)? "s" : ((to == t)? "t" : to_string(to)));

    char* x = new char[100];
    sprintf(x, "Edge %s -> %s | flow = %7.3lf | capacity = %7.3lf | is residual : %d",
      u.c_str(),
      v.c_str(),
      flow,
      capacity,
      isResidual());
    return x;
  }


};


class NetworkFlowSolverBase{
public:

  NetworkFlowSolverBase(int _n, int _s, int _t): visited(_n, 0){
    n = _n;
    s = _s;
    t = _t;
    solved = 0;
    maxFlow = 0;
    visitedToken = 1;
    initEmptyFlowGraph();

  }

  void addEdge(int from, int to, double capacity){
    if(capacity <= 0){
      throw invalid_argument("Forward edge capacity <= 0");
    }

    // Edge* e1 = new Edge(from, to, capacity);
    // Edge* e2 = new Edge(to, from, 0);
    // e1.residual = &e2;
    // e2.residual = &e1;
    graph[from].emplace_back(from, to, capacity);
    graph[to].emplace_back(to, from, 0);
    graph[to].back().residual = &(graph[from].back());
    graph[from].back().residual = &(graph[to].back());
  }

  vector<list<Edge>> getGraph(){
    execute();
    return graph;
  }

  double getMaxFlow(){
    execute();
    return maxFlow;
  }

  void visit(int i){
    visited[i] = visitedToken;
  }

  bool isVisited(int i){
    return visited[i] == visitedToken;
  }

  void markAllNodesAsUnvisited(){
    visitedToken++;
  }

protected:
  double INF = 999999.0;

  int n, s, t;

  int visitedToken;
  vector<int> visited;

  bool solved;

  double maxFlow;
  vector<list<Edge>> graph;

  void initEmptyFlowGraph(){
    graph = vector<list<Edge>>(n, list<Edge>());
  }

  void execute(){
    if(solved) return;
    solved = true;
    solve();
  }

  virtual void solve(){
    cout << "shold not be exe" << endl;
  }


};

class EdmondsKarpSolver : public NetworkFlowSolverBase{
public:


    EdmondsKarpSolver(int _n, int _s, int _t):
      NetworkFlowSolverBase(_n, _s, _t){

    }

private:

  double min(double a, double b){
    if(a > b) return b;
    return a;
  }

  void solve(){

    double flow;
    do{
      markAllNodesAsUnvisited();
      flow = bfs();
      maxFlow += flow;
    }while(flow != 0);


  }


  double bfs(){
    cout << 'c' <<endl;
    queue<int> q;

    visit(s);
    q.push(s);

    vector<Edge*> prev(n);
    while(!q.empty()){
      int node = q.front();
      q.pop();

      if(node == t) break;

      for(Edge &edge : graph[node]){
        double cap = edge.remainingCapacity();
        if(cap > 0 && !isVisited(edge.to)){
          visit(edge.to);
          prev[edge.to] = &edge;
          q.push(edge.to);
        }
      }
    }

    if(prev[t] == nullptr) return 0;

    double bottleNeck = INF;
    for(auto edge = prev[t]; edge != nullptr; edge = prev[edge->from]){
      bottleNeck = min(bottleNeck, edge->remainingCapacity());
    }

    for(auto edge = prev[t]; edge != nullptr; edge = prev[edge->from]){
      edge->augment(bottleNeck);
    }

    return bottleNeck;

  }
};

int main(){


  int n = 11;

  int s = n-2;
  int t = n-1;

  EdmondsKarpSolver ff(n, s, t);
  NetworkFlowSolverBase& solver = ff;

  //from source
  solver.addEdge(s, 0, 10);
  solver.addEdge(s, 1, 5);
  solver.addEdge(s, 2, 10);

  // middle
  solver.addEdge(0, 3, 10);
  solver.addEdge(1, 2, 10);
  solver.addEdge(2, 5, 15);
  solver.addEdge(3, 1, 2);
  solver.addEdge(3, 6, 15);
  solver.addEdge(4, 1, 15);
  solver.addEdge(4, 3, 3);
  solver.addEdge(5, 4, 4);
  solver.addEdge(5, 8, 10);
  solver.addEdge(6, 7, 10);
  solver.addEdge(7, 4, 10);
  solver.addEdge(7, 5, 7);

  // sink
  solver.addEdge(6, t, 15);
  solver.addEdge(8, t, 10);
try{


  printf("Maximum flow is %lf\n", solver.getMaxFlow());

}catch(exception e){
  cout << e.what() << endl;
}

  vector<list<Edge>> result = solver.getGraph();
  for(auto edges : result){
    for(auto e : edges){
      cout << e.toString(s, t) << endl;
    }
  }

  cout << "end" << endl;
  return 0;
}
