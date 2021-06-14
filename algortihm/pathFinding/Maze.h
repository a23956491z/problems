//
// Created by a2395 on 2021/5/1.
//

#ifndef PATHFINDING_MAZE_H
#define PATHFINDING_MAZE_H

#include "Node.h"
#include <vector>
#include <list>
#include <queue>
#include <utility>
#include <string>
#include <windows.h>
using std::vector;
using std::cout;
using std::endl;
using std::list;
using std::priority_queue;
using std::pair;
using std::make_pair;
using std::string;

class Maze{

    vector<vector<Node>> maze;
    int maze_size;

    list<Node> path;

public:
    static void setCursorPosition(int x, int y)
    {
        static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        std::cout.flush();
        COORD coord = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(hOut, coord);
    }
    enum Direction {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    explicit Maze(int n);
    Maze(const std::string& file_name);

    int size() const    {
        return maze_size;
    }

    vector<vector<Node>>& maze_vector(){

        return maze;
    }

    Node &indexing(Node &n){
        return maze[n.i][n.j];
    }
    Node front() const{

        return maze[0][0];
    }
    Node back() const{

        return maze[maze_size-1][maze_size-1];
    }
    void print() const{

        for(int i = 0; i != maze.size()+2; i++) cout << "O ";
        cout << endl;

        for(auto &i : maze){
            cout << "O ";
            for(int j = 0; j != i.size(); j++){
                cout << i[j] ;
            }

            cout << "O"<< endl;
        }
        for(int i = 0; i != maze.size()+2; i++) cout << "O ";
        cout << endl;
        cout << endl << endl;
    }

    void set_wall(Node n, int i){
        maze[n.i][n.j].wall = i;
    }

    Node shift(Node n, Direction dir) const;

    void sub_find_path(Node n, int &not_lock);
    int find_path();
};
class PathFinder;

class AdjacencyList{
    class AdjNode;
    class AdjNode{
    public:
        int destination;
        int weight;

        AdjNode(int dest, int weight):destination(dest), weight(weight){

        }

    };

public:
    vector<list<AdjNode*>> arr;
    int size;


    friend PathFinder;
    AdjacencyList(int n): arr(n, list<AdjNode*>()){
        size = n;
    }


    int addEdge(int src, int dest, int weight=1, bool bidirectional = true){

        if(src < 0 || dest < 0) return 0;
        if(src >= size || dest >= size) return 0;

        arr[src].push_back(new AdjNode(dest, weight));
        if(bidirectional)
            arr[dest].push_back(new AdjNode(src, weight));

        return 1;
    }

    void print(){
        for(int i = 0; i != size; i++){
            cout << i << ": ";
            for(auto v : arr[i]){
                cout << v->destination << " ";
            }

            cout << "\n";
        }
    }

};

class PathFinder{
    AdjacencyList adj;
    Maze &maze;
    vector<int> distance;
    vector<int> predecessor;
    vector<int> visited;

    int indexing(Node n){
        return n.i * maze.size() + n.j;
    }
public:
    PathFinder(Maze& maze):
    adj(maze.size()*maze.size()),
    maze(maze),
    distance(adj.size, 0),
    predecessor(adj.size, -1),
    visited(adj.size, 0)
    {



        int n = maze.size();

        static Maze::Direction direction[4] = {Maze::UP, Maze::RIGHT, Maze::DOWN, Maze::LEFT};

        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){

                int flatten_index = i * n + j;
                if(maze.maze_vector()[i][j].wall == 1) continue;

                for(int dir = 0; dir != 4; dir++){
                    Node side_node = maze.shift(Node(i,j), direction[dir]);
                    if(side_node.wall==0){
                        adj.addEdge(flatten_index, indexing(side_node), 1, false);
                    }
                }
            }
        }

        //adj.print();




    }
    void relax(int from, int to, int weight){
        if(distance[to] > distance[from] + weight){
            distance[to] = distance[from] + weight;
            predecessor[to] = from;
        }
    }

    void dijkstra(int src, int goal=-1, bool animation=false){

        if(maze.maze_vector()[src/maze.size()][src%maze.size()].wall==1) return;
        if(maze.maze_vector()[goal/maze.size()][goal%maze.size()].wall==1) return;

        if(goal == -1) goal = adj.size-1;
        typedef pair<int, int> pi;
        std::priority_queue<pi, vector<pi>, std::greater<>> heap;

        for(int i = 0; i != adj.size; i++){
            distance[i] = i != src ? INT_MAX : 0;
            heap.push(make_pair( distance[i], i));

        }

        while(!heap.empty()){

            int vertex = heap.top().second;
            heap.pop();
            if(goal && vertex == goal) break;

            if(visited[vertex]) continue;

            visited[vertex] = 1;

            for(auto des : adj.arr[vertex]){
                if(animation){
                    Maze::setCursorPosition(0,0);
                    maze.print();
                    Sleep(10);
                }


                int des_index = des->destination;
                maze.maze_vector()[des_index/maze.size()][des_index%maze.size()].wall = 2;
                relax(vertex, des_index, des->weight);
                heap.push(make_pair(distance[des_index],des_index));
            }
        }
/*
        for(int i = 0; i != adj.size; i++){
            cout << i << ": " << distance[i] << " pre: " << predecessor[i] << endl;
        }
*/
        int pre = goal;
        while(pre != -1){
            int i = pre / maze.size();
            int j = pre % maze.size();
            maze.maze_vector()[i][j].wall = 3;
            pre = predecessor[pre];
        }
        if(animation) system("cls");
        maze.print();


    }
};
#endif //PATHFINDING_MAZE_H
