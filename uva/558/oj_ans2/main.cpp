#include <iostream>
#include <vector>

using namespace std;

const int INF = 1000000;
bool check(vector<vector<int>>& vv){

    int total_vertex = static_cast<int>(vv.size());
    vector<vector<int>>& adj_table = vv;

    for(int k = 0; k != total_vertex; k++){
        for(int i = 0; i != total_vertex; i++){
            for(int j = 0; j != total_vertex; j++){
                if(adj_table[i][j] > adj_table[i][k] + adj_table[k][j]){
                    adj_table[i][j] = adj_table[i][k] + adj_table[k][j];

                    if(i == j & adj_table[i][j] < 0){
                        return true;
                    }
                }
            }
        }
    }

    return false;
}
int main() {
    int cases = 0;
    cin >> cases;

    for(int current_case = 0; current_case != cases; current_case++){
        int total_vertex = 0, total_edge = 0;
        cin >> total_vertex >> total_edge;

        vector<vector<int>> adj_table(total_vertex, vector<int>(total_vertex, INF));

        for(int i = 0; i != total_vertex; i++){
            adj_table[i][i] = 0;
        }

        for(int current_edge = 0; current_edge != total_edge; current_edge++){
            int src = 0, des = 0, weight = 0;
            cin >> src >> des >> weight;

            if(weight < adj_table[src][des]){
                adj_table[src][des] = weight;
            }

        }

        if(check(adj_table)){
            cout << "possible" << endl;
        }else{
            cout << "not possible" << endl;
        }

    }
    return 0;
}
