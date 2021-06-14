//
// Created by a2395 on 2021/5/1.
//

#include "Maze.h"
#include <fstream>
Maze::Maze(int n){

    maze_size = n;

    for(int i = 0; i != n; i++) {

        vector<Node> vec;
        for (int j = 0; j != n; j++) {

            Node tmp(i, j);
            vec.push_back(tmp);
        }

        maze.push_back(vec);
    }
}
Maze::Maze(const std::string& file_name){

    std::ifstream infile(file_name);


    int i = 0;
    std::string line;
    while (std::getline(infile, line))
    {

        vector<Node> vec;
        for(int j = 0; j != line.size(); j++){

            Node tmp(i,j);
            if(line[j] == '0'){
                tmp.wall = 0;
            }
            else{
                tmp.wall = 1;
            }
            vec.push_back(tmp);


        }

        maze.push_back(vec);
        i++;
    }

    maze_size=i;
}

void Maze::sub_find_path(Node n, int &not_lock){
    static Direction direction[4] = {Maze::UP, Maze::RIGHT, Maze::DOWN, Maze::LEFT};


    if(n.isNull() || !not_lock || n.wall == -1 || n.wall == 1){
        return;
    }else{
        int have_path = 0;
        path.push_back(n);
        maze[n.i][n.j].wall = -1;

        Node goal = back();
        if(n == goal){

            not_lock = 0;
            return;
        }
        for(auto dir : direction){

            sub_find_path(shift(n, dir), not_lock);

        }

    }


}

Node Maze::shift(Node n, Direction dir) const{

    if(dir == UP){
        int shifted = n.i - 1;
        return ((shifted < 0) ? Node() : maze[shifted][n.j]);
    }
    if(dir == RIGHT){
        int shifted = n.j + 1;
        return ((shifted >= maze_size) ? Node() : maze[n.i][shifted]);
    }
    if(dir == DOWN){
        int shifted = n.i + 1;
        return ((shifted >= maze_size) ? Node() : maze[shifted][n.j]);
    }
    if(dir == LEFT){
        int shifted = n.j - 1;
        return ((shifted < 0) ? Node() : maze[n.i][shifted]);
    }

    return Node();
}
int Maze::find_path(){
    int not_lock = 1;
    sub_find_path(front(), not_lock);

    /*if(not_lock)*/print();
    for(auto &i : maze){
        for(auto &j : i){
            if(j.wall == -1) j.wall = 0;
        }
    }


    return not_lock;

}