//
// Created by a2395 on 2021/5/1.
//

#ifndef PATHFINDING_NODE_H
#define PATHFINDING_NODE_H
#include <iostream>

class Node {
public:
    int i, j;
    int wall;

    Node();
    Node(int _i, int _j);

    Node(const Node& node);

    bool isNull() const;
    bool operator==(Node &node) const;


    void print_index() const;
    friend std::ostream& operator<<(std::ostream& os, const  Node &node);
};


#endif //PATHFINDING_NODE_H
