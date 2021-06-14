#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct Edge {int a, b, r, w;} edge[1000];
int en = 0;
vector<int> adj[10];

void addedge(int a, int b, int c, int w)
{
    // 加入一條邊
    edge[en] = (Edge){a, b, c, +w};
    adj[a].push_back(en++);
    // 同時也加入反向邊
    edge[en] = (Edge){b, a, 0, -w};
    adj[b].push_back(en++);
}

// Label Correcting Algorithm
int p[10], d[10];   // 最短路徑樹、最短路徑長度
int index[10];      // 最短路徑樹對應的邊的索引值
bool inqueue[10];   // 記錄各個點是否在queue當中

void MinCostMaxstFlow(int s, int t)
{
    int flow = 0, cost = 0; // 最小成本最大流的流量與成本

    while (true)
    {
        // 實施 Label Correcting Algorithm，
        // 從剩餘網路上面，找到成本最小的擴充路徑。
        for (int i=0; i<10; ++i) d[i] = 1e9;
        d[s] = 0;
        queue<int> Q;
        Q.push(s);
//      inqueue[s] = true;

        while (!Q.empty())
        {
            int a = Q.front(); Q.pop();
            inqueue[a] = false;
            for (int i=0; i<adj[a].size(); ++i)
            {
                Edge& e = edge[adj[a][i]];
                int b = e.b;
                if (e.r > 0 && d[a] + e.w < d[b])
                {
                    d[b] = d[a] + e.w;
                    p[b] = a;
                    index[b] = adj[a][i];

                    if (!inqueue[b])
                    {
                        Q.push(b);
                        inqueue[b] = true;
                    }
                }
            }
        }

        cout << "DIST------------------------" << endl;
        for(int i = 0; i != 7; i++){
            printf(" %d -> %d | cost : %d\n", s, i, d[i]);
        }
        cout << "DIST------------------------" << endl;
        cout << "PREV------------------------" << endl;
        for (int a = t; a != s; a = p[a])
        {

            printf(" %d ", a);
            if(p[a] != s){
                printf("-> ");
            }else{
                printf("-> %d\n", s);
            }
        }
        cout << "PREV------------------------" << endl;
        // 已經找不到擴充路徑
        if (d[t] == 1e9) break;

        // 計算擴充路徑的流量，並且進行擴充。
        int df = 1e9;
        for (int a = t; a != s; a = p[a])
        {
            int i = index[a];
            df = min(df, edge[i].r);
        }
        for (int a = t; a != s; a = p[a])
        {
            int i = index[a];
            edge[i].r -= df;
            edge[i^1].r += df;
        }
        flow += df;
        cost += df * d[t];
    }

    cout << "最大流的流量是" << flow << endl;
    cout << "最小成本最大流的成本是" << cost << endl;
}

int main(){
    int n = 7;

    int s = n - 2;
    int t = n - 1;

    addedge(s, 0, 1, 0);
    addedge(s, 1, 1, 0);


    // middle
    addedge(0, 2, 1, 10);
    addedge(0, 3, 1, 100);
    addedge(0, 4, 1, 15);
    addedge(1, 2, 1, 15);
    addedge(1, 3, 1, 200);
    addedge(1, 4, 1, 30);

    // sink
    addedge(2, t, 1, 0);
    addedge(3, t, 1, 0);
    addedge(4, t, 1, 0);

    MinCostMaxstFlow(s,t);
}
