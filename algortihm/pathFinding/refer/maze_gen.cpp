#include <iostream>
#include <list>
#include <vector>
#include <random>
#include <ctime>
#include <set>
#include<windows.h>

using namespace std;

class Node{

public :
    int i, j;
    int wall;

    Node(){
        i = -1;
        j = -1;
        wall = -1;
    }
    Node(int _i, int _j){
        i = _i;
        j = _j;
        wall = 1;
    }

    Node(const Node& node){
        i = node.i;
        j = node.j;
        wall = node.wall;
    }


    bool isNull() const{
        return wall==-1;
    }
    bool operator==(Node &node) const{
        return (i==node.i)&&(j==node.j);
    }


    /*
    Node operator=(Node &node){
        return Node(node);
    }*/
    void print_index() const{
        cout << "(" << i << ", " << j << ")";
    }

    friend ostream& operator<<(ostream& os, const  Node &node);
};
ostream& operator<<(ostream& os, const  Node &node) {

    if (node.wall == 0) {
        os << "  ";
    } else if (node.wall == 1) {
        os << "O ";
    } else {
        os << ". ";
    }
    return os;
}

class Maze{

    vector<vector<Node>> maze;
    int maze_size;

    list<Node> path;

public:
    enum Direction {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    explicit Maze(int n){

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

    int size() const{
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

    Node shift(Node n, Direction dir) const{

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

    void sub_find_path(Node n, int &not_lock){
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
    int find_path(){
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
};

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

    explicit Create_maze_manager(Maze &maze,default_random_engine &gen, default_form form = DIGOUT_BEGIN_END)
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
            maze_ptr->print();
        }





    }

    void remove_node_from_list(Node node){
        for(auto iter = waiting_list.begin(); iter != waiting_list.end(); iter++){
            if(*iter == node){
                waiting_list.erase(iter);
                break;
            }
        }
    }
    void break_specific_wall(Node node){

        remove_node_from_list(node);
        maze_ptr->set_wall(node, 0);
    }

    Node random_take_out(){
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

    void breaking_walls(){
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
/*
            Sleep(50);
            system("cls");
            maze_ptr->print();
*/
        }

    }

};

/*
int main(){

    default_random_engine gen(time(nullptr));


    int counter = 0;
    for(int i = 0; i != 1; i++){
        Maze maze(25);

        Create_maze_manager manager(maze, gen, Create_maze_manager::PREDIG_GRID);
        Node_set s(maze);
        manager.breaking_walls();

       if(!maze.find_path()) counter++;
    }

    cout << counter << endl;

}
*/