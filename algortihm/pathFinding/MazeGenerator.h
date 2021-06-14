//
// Created by a2395 on 2021/5/1.
//

#ifndef PATHFINDING_MAZEGENERATOR_H
#define PATHFINDING_MAZEGENERATOR_H
#include "Node.h"
#include "Maze.h"
#include <vector>
#include <random>
#include <set>

using std::vector;
using std::set;
using std::default_random_engine;
using std::uniform_int_distribution;

class Node_set{

    vector<int> set;

    int maze_size;

public:
    explicit Node_set(Maze &maze){

        maze_size = maze.size();
        set.resize(maze_size*maze_size, -1);
    }
    int indexing(Node &n) const{
        return n.i * maze_size + n.j;
    }
    int size() const{
        return set.size();
    }
    int find_set(int i){
        if(set[i] < 0) return i;
        return find_set(set[i]);
    }
    int node_find_set(Node &n){
        return find_set(indexing(n));
    }


    int collapsing(int i){

        int root = find_set(i);

        while(i != root){
            int tmp = set[i];
            set[i] = root;
            i = tmp;
        }

        return root;
    }

    int union_set(int x, int y){

        int root_x = collapsing(x);
        int root_y = collapsing(y);

        if(root_x == root_y) return root_x;

        if(set[root_x] > set[root_y]){
            set[root_y] += set[root_x];
            set[root_x] = root_y;
            return root_x;
        }else{
            set[root_x] += set[root_y];
            set[root_y] = root_x;
            return root_y;
        }
    }

};


class Create_maze_manager{

    list<Node> waiting_list;
    Maze *maze_ptr;


    default_random_engine generator;
    Node_set set_nodes;
public:
    enum default_form{
        NON_PREPROCESSING,
        DIGOUT_BEGIN_END,
        PREDIG_GRID
    };

    explicit Create_maze_manager(Maze &maze,default_random_engine &gen, default_form form);


    void remove_node_from_list(Node node);
    void break_specific_wall(Node node);

    Node random_take_out();

    void breaking_walls(bool);
};


#endif //PATHFINDING_MAZEGENERATOR_H
