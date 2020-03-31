//
// Created by jedra on 30.03.2020.
//

#ifndef FIFTHTEEN_NODE_H
#define FIFTHTEEN_NODE_H


#include <string>
#include "../include/Puzzle.h"


class Node {
public:
    bool visited = false;
    std::string path;
    Node* neighbours[4]{};
    void initNeighbours(Puzzle p);
    Node(std::string path);
    Node();
    Node * getNeighbour(char c);
};

// this['L']


#endif //FIFTHTEEN_NODE_H
