#include <iostream>
#include "Node.h"
#include <random>
#include "MazeGenerator.h"
#include <time.h>
#include <windows.h>

using namespace std;
int main() {

    system("PAUSE");
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    default_random_engine gen(time(nullptr));

   // Maze maze("../test_data/1.txt");

    system(("chcp " + std::to_string(CP_UTF8)).c_str());
    system("cls");


    Maze maze(20);
    Create_maze_manager manager(maze, gen, Create_maze_manager::PREDIG_GRID);
    Node_set s(maze);
    manager.breaking_walls(true);

    //maze.print();
    PathFinder pf(maze);
    pf.dijkstra(0, -1 ,true);

    system("PAUSE");
    return 0;
}
