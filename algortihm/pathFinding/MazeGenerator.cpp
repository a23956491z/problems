//
// Created by a2395 on 2021/5/1.
//

#include "MazeGenerator.h"

Create_maze_manager::Create_maze_manager(Maze &maze,default_random_engine &gen, default_form form = DIGOUT_BEGIN_END)
        :generator(gen), set_nodes(maze)
{
    maze_ptr = &maze;

    for(auto &i : maze.maze_vector()){
        for(auto &j : i){
            waiting_list.push_back(j);
        }
    }
    int size = maze_ptr->size();
    if(form == DIGOUT_BEGIN_END){

        Node tmp[6] = {maze_ptr->back(),
                       maze_ptr->front(),

                       maze_ptr->shift(maze_ptr->back(), Maze::UP),
                       maze_ptr->shift(maze_ptr->back(), Maze::LEFT),
                       maze_ptr->shift(maze_ptr->front(), Maze::DOWN),
                       maze_ptr->shift(maze_ptr->front(), Maze::RIGHT)};
        for(int i = 0; i != 2; i++) break_specific_wall(tmp[i]);

        if(size >= 3){
            for(int i = 2; i != 6; i++) break_specific_wall(tmp[i]);

            set_nodes.union_set(set_nodes.indexing(tmp[0]) ,set_nodes.indexing(tmp[2]));
            set_nodes.union_set(set_nodes.indexing(tmp[0]) ,set_nodes.indexing(tmp[3]));
            set_nodes.union_set(set_nodes.indexing(tmp[1]) ,set_nodes.indexing(tmp[4]));
            set_nodes.union_set(set_nodes.indexing(tmp[1]) ,set_nodes.indexing(tmp[5]));
        }
    }
    if(form == PREDIG_GRID){
        break_specific_wall(maze_ptr->back());
        for(int i = 0; i < size; i++){
            for(int j = (i%2); j < size; j+=2){
                if(i%2 == 0)break_specific_wall(Node(i,j));
                else  remove_node_from_list(Node(i,j));
            }
        }
        //maze_ptr->print();
    }
}

void Create_maze_manager::remove_node_from_list(Node node){
    for(auto iter = waiting_list.begin(); iter != waiting_list.end(); iter++){
        if(*iter == node){
            waiting_list.erase(iter);
            break;
        }
    }
}
void Create_maze_manager::break_specific_wall(Node node){

    remove_node_from_list(node);
    maze_ptr->set_wall(node, 0);
}



Node Create_maze_manager::random_take_out(){
    int n = waiting_list.size();

    Node tmp;
    if(n == 0) return tmp;


    uniform_int_distribution<int> distribution(0,n);

    while(tmp.isNull()){
        for(auto iter = waiting_list.begin(); iter != waiting_list.end(); iter++){

            if(!distribution(generator)){

                tmp = *iter;
                waiting_list.erase(iter);

                break;
            }
        }
    }

    return tmp;
}

void Create_maze_manager::breaking_walls(bool animation=false){
    Maze::Direction direction[4] = {Maze::UP, Maze::RIGHT, Maze::DOWN, Maze::LEFT};

    int waiting_list_size = waiting_list.size();
    for(int i = 0; i != waiting_list_size; i++) {
        Node n = random_take_out();

        int has_loop = 0;
        set<int> set_roots;
        for (auto dir : direction) {
            Node tmp_node = maze_ptr->shift(n, dir);
            if (!tmp_node.isNull() && tmp_node.wall == 0) {
                int root = set_nodes.node_find_set(tmp_node);

                if (set_roots.count(root)) {

                    has_loop = 1;
                } else {
                    set_roots.insert(root);
                }

            }
        }

        if (!has_loop){
            for(auto &j : set_roots){
                set_nodes.union_set(set_nodes.indexing(n), j);
            }
            maze_ptr->set_wall(n, 0);
        }
            if(animation){
                Sleep(50);
                Maze::setCursorPosition(0,0);
                maze_ptr->print();
            }


    }

}