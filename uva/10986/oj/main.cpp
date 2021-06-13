#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>
using namespace std;

int main() {
    int cases = 0;
    cin >> cases;

    for(int current_case = 0; current_case != cases; current_case++){

        int total_server = 0, total_cable = 0,
            server_src = 0, server_des = 0;
        cin >> total_server >> total_cable >> server_src >> server_des;

        //printf("START: %d, GOAL: %d\n", server_src, server_des);
        vector< vector<int>> adj_table(total_server, vector<int>(total_server, INT_MAX));
        vector< int> distance(total_server, INT_MAX);
        vector< int> visited(total_server, 0);

        for(int current_cable = 0; current_cable != total_cable; current_cable++){
            int src, des, weight;
            cin >> src >> des >> weight;

            if(weight < adj_table[src][des]){
                adj_table[src][des] = weight;
                adj_table[des][src] = weight;
            }

        }

        typedef pair<int, int> pi;
        std::priority_queue<pi, vector<pi>, std::greater<>> heap;
        // puts pair(distance from src, vertex)

        distance[server_src] = 0;
        heap.push(make_pair( 0, server_src));

        while(!heap.empty()){
            int vertex = heap.top().second;
            heap.pop();

            if(vertex == server_des) break;
            if(visited[vertex]) continue;
            visited[vertex] = 1;

            for(int i =0; i != total_server; i++){

                if(adj_table[vertex][i] == INT_MAX || distance[vertex]  == INT_MAX) {
                    continue;
                }
                // relax
                if(distance[i] > distance[vertex] + adj_table[vertex][i]){
                    distance[i] = distance[vertex] + adj_table[vertex][i];
                }
                heap.push(make_pair(distance[i],i));
            }

        }

        printf("Case #%d: ", current_case+1);

        if(distance[server_des] == INT_MAX){
            cout << "unreachable"<<endl;
        }else{
            cout << distance[server_des] << endl;
        }

    }

    return 0;
}
