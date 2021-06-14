#include <vector>
#include <limits>
#include <iostream>

using namespace std;

#define _min(a,b) (a)<(b) ? (a) : (b)

const double DOUBLE_POSITIVE_INF = numeric_limits<double>::max();
const double DOUBLE_NEGATIVE_INF = numeric_limits<double>::lowest();

class Edge{
public:
    double cost;
    int from, to;

    Edge(int _from, int _to, double _cost){
        from = _from;
        to = _to;
        cost = _cost;
    }
};

// V is vertex number
vector<double> bellmanFord(vector<Edge> &edges, int V, int start){

    // distance table
    vector<double> dist(V, DOUBLE_POSITIVE_INF);
    dist[start] = 0;

    // relax every edges on vertexs
    // iterate V-1 times
    for(int v = 0; v != V-1; v++){

        // relax every edge
        for(auto &edge : edges){

            // relax
            /*
            if(dist[edge.from] + edge.cost <  dist[edge.to]){
                dist[edge.to] = dist[edge.from] + edge.cost;
            }*/

            // or this way
            dist[edge.to] = _min(dist[edge.to], dist[edge.from] + edge.cost);
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

int main(){
    // 9 vertexes
    int  V = 9, start = 0;

    // 10 edges
    vector<Edge> edges;
    edges.emplace_back(0,1,1);
    edges.emplace_back(1,2,1);
    edges.emplace_back(2,4,1);
    edges.emplace_back(4,3,-3);
    edges.emplace_back(3,2,1);
    edges.emplace_back(1,5,4);
    edges.emplace_back(1,6,4);
    edges.emplace_back(5,6,5);
    edges.emplace_back(6,7,4);
    edges.emplace_back(5,7,3);

    vector<double> d = bellmanFord(edges, V, start);

    for(int i = 0; i != V; i++){
        cout << "The code to get from node " << start << " to " << i;
        cout << " is ";

        if(d[i] == DOUBLE_POSITIVE_INF)       cout << "Infinity";
        else if(d[i] == DOUBLE_NEGATIVE_INF)  cout << "-Infinity";
        else                                  cout << d[i];

        cout << endl;


    }

}
