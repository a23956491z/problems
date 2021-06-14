#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <queue>
#include <algorithm>
#include <limits>


using namespace std;


const double DOUBLE_POSITIVE_INF = numeric_limits<double>::max();
const double DOUBLE_NEGATIVE_INF = numeric_limits<double>::lowest();


class Edge;

class Edge {
public:
    int from, to;
    double flow;
    double cost;
    double capacity;
    Edge *residual;

    Edge(int f, int t, double c, double _cost=0)
    {
        from     = f;
        to       = t;
        capacity = c;
        flow     = 0;
        cost = _cost;
    }

    bool isResidual()
    {
        return capacity == 0;
    }

    double remainingCapacity()
    {
        return capacity - flow;
    }

    void augment(double bottleNeck)
    {
        if (residual == nullptr)
        {
            printf("NULLPTR!!\n");
            return;
        }
        flow           += bottleNeck;
        residual->flow -= bottleNeck;
        //cout << "AUG" <<toString(-1,-1) << endl;
    }

    string toString(int s, int t)
    {
        string u((from == s)? "s" : ((from == t)? "t" : to_string(from)));
        string v((to == s)? "s" : ((to == t)? "t" : to_string(to)));

        char *x = new char[100];

        sprintf(x, "Edge %s -> %s | cost = %3.0lf | flow = %7.3lf | capacity = %7.3lf | is residual : %d",
                u.c_str(),
                v.c_str(),
                cost,
                flow,
                capacity,
                isResidual());
        return x;
    }
};


class NetworkFlowSolverBase {
public:

    NetworkFlowSolverBase(int _n, int _s, int _t) : visited(_n, 0)
    {
        n            = _n;
        s            = _s;
        t            = _t;
        solved       = 0;
        maxFlow      = 0;
        visitedToken = 1;
        initEmptyFlowGraph();
    }

    void addEdge(int from, int to, double capacity, double cost = 0)
    {
        if (capacity <= 0)
        {
            throw invalid_argument("Forward edge capacity <= 0");
        }

        // Edge* e1 = new Edge(from, to, capacity);
        // Edge* e2 = new Edge(to, from, 0);
        // e1.residual = &e2;
        // e2.residual = &e1;
        graph[from].emplace_back(from, to, capacity, cost);
        graph[to].emplace_back(to, from, 0, -cost);
        graph[to].back().residual   = &(graph[from].back());
        graph[from].back().residual = &(graph[to].back());
    }

    vector<list<Edge> > getGraph()
    {
        execute();
        return graph;
    }

    double getMaxFlow()
    {
        execute();
        return maxFlow;
    }
    double getMinCost()
    {
        execute();
        return totalCost;
    }
    void visit(int i)
    {
        visited[i] = visitedToken;
    }

    bool isVisited(int i)
    {
        return visited[i] == visitedToken;
    }

    void markAllNodesAsUnvisited()
    {
        visitedToken++;
    }

protected:
    double INF = 999999.0;

    int n, s, t;

    int visitedToken;
    vector<int> visited;

    bool solved;

    double maxFlow;
    double totalCost;
    vector<list<Edge> > graph;

    void initEmptyFlowGraph()
    {
        graph = vector<list<Edge> >(n, list<Edge>());
    }

    void execute()
    {
        if (solved) { return; }
        solved = true;
        solve();
    }

    virtual void solve()
    {
        cout << "shold not be exe" << endl;
    }
};

class EdmondsKarpSolver : public NetworkFlowSolverBase {
public:


    EdmondsKarpSolver(int _n, int _s, int _t) :
        NetworkFlowSolverBase(_n, _s, _t),
        prev(n), inqueue(n, false)
    {
        totalCost = 0;
        maxFlow = 0;
    }

private:
    vector<Edge *> prev;
    vector<bool> inqueue;
    double min(double a, double b)
    {
        if (a > b) { return b; }
        return a;
    }

    void solve()
    {
        double flow;

        do
        {
            markAllNodesAsUnvisited();
            flow     = bfs();
            maxFlow += flow;

        }while (flow != 0);


    }

    vector<double> bellmanFord(vector<Edge> &edges, int V, int start){

        // distance table
        vector<double> dist(V, DOUBLE_POSITIVE_INF);
        dist[start] = 0;

        // relax every edges on vertexs
        // iterate V-1 times
        for(int v = 0; v != V-1; v++){

            // relax every edge
            for(auto &edge : edges){

                dist[edge.to] = min(dist[edge.to], dist[edge.from] + edge.cost);
            }
        }

        for(int v = 0; v != V-1; v++){
            for(auto &edge : edges){
                if(dist[edge.from] + edge.cost < dist[edge.to]){
                    dist[edge.to] = DOUBLE_NEGATIVE_INF;
                }
            }
        }
        return dist;
    }
    double bfs()
    {
        vector<double> dist(n, DOUBLE_POSITIVE_INF);
        dist[s] = 0;



        queue<int> q;

        visit(s);
        q.push(s);

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            visited[node]--;
            //if (node == t) { break; }

            for (Edge& edge : graph[node])
            {
                double cap = edge.remainingCapacity();
                if ((cap > 0) &&
                        dist[edge.from] + edge.cost < dist[edge.to])
                {
                    dist[edge.to] = dist[edge.from] + edge.cost;
                    prev[edge.to] = &edge;

                    if(!isVisited(edge.to)){
                        visit(edge.to);
                        q.push(edge.to);
                    }

                }
            }
        }
        if(dist[t] == DOUBLE_POSITIVE_INF) return 0;

        cout << "DIST--------------" << endl;
        for(int i = 0; i != n; i++){
            if(dist[i] == DOUBLE_POSITIVE_INF){
                printf("%d -> %d | dis: INF\n", s, i);
            }else{
                printf("%d -> %d | dis: %3.0lf\n", s, i, dist[i]);
            }

        }
        cout << "DIST--------------" << endl;



        double bottleNeck = INF;

        for (auto edge = prev[t]; edge != nullptr; edge = prev[edge->from])
        {
            bottleNeck = min(bottleNeck, edge->remainingCapacity());
        }
        cout << "BOTTLENECK : "<< bottleNeck <<endl;
        for (auto edge = prev[t]; edge != nullptr; edge = prev[edge->from])
        {
            edge->augment(bottleNeck);
        }

        totalCost += bottleNeck * dist[t];
        return bottleNeck;
    }
};

int main()
{
    int n = 7;

    int s = n - 2;
    int t = n - 1;

    EdmondsKarpSolver      ff(n, s, t);
    NetworkFlowSolverBase& solver = ff;

    //from source
    solver.addEdge(s, 0, 1);
    solver.addEdge(s, 1, 1);


    // middle
    solver.addEdge(0, 2, 1, 10);
    solver.addEdge(0, 3, 1, 100);
    solver.addEdge(0, 4, 1, 15);
    solver.addEdge(1, 2, 1, 15);
    solver.addEdge(1, 3, 1, 200);
    solver.addEdge(1, 4, 1, 30);

    // sink
    solver.addEdge(2, t, 1);
    solver.addEdge(3, t, 1);
    solver.addEdge(4, t, 1);
    try{
        printf("Maximum flow is %lf\n", solver.getMaxFlow());
        printf("Minimum cost is %lf\n", solver.getMinCost());
    }
    catch (exception e) {
        cout << e.what() << endl;
    }

    vector<list<Edge> > result = solver.getGraph();

    for (auto edges : result)
    {
        for (auto e : edges)
        {
            if(e.isResidual()) continue;
            cout << e.toString(s, t) << endl;
        }
    }

    cout << "end" << endl;
    return 0;
}
