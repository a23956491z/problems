//
// Created by a2395 on 2021/5/1.
//

#include "Node.h"
#include <iostream>


Node::Node(){
    i = -1;
    j = -1;
    wall = -1;
}
Node::Node(int _i, int _j){
    i = _i;
    j = _j;
    wall = 1;
}

Node::Node(const Node& node){
    i = node.i;
    j = node.j;
    wall = node.wall;
}


bool Node::isNull() const{
    return wall==-1;
}
bool Node::operator==(Node &node) const{
    return (i==node.i)&&(j==node.j);
}


/*
Node operator=(Node &node){
    return Node(node);
}*/
void Node::print_index() const{
    std::cout << "(" << i << ", " << j << ")";
}


std::ostream& operator<<(std::ostream& os, const  Node &node) {

    if (node.wall == 0) {
        os << "  ";
    } else if (node.wall == 1) {
        os << "O ";
    } else if (node.wall == 2) {
        os << "\033[90m. \033[0m";
    }
    else {
        os << "\033[91;1m. \033[0m";
    }
    return os;
}