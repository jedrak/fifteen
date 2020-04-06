//
// Created by jedra on 30.03.2020.
//

#include "../include/Node.h"

#include <utility>



//std::string &Node::operator[](char) {
//    return <#initializer#>;



void Node::initNeighbours(Puzzle p) {
    std::string possibleMoves = p.possibleMoves();
    for(char c : possibleMoves){
        int whichCmd;

        switch (c){
            case 'L':
                whichCmd = 0;
                break;
            case 'R':
                whichCmd = 1;
                break;
            case 'U':
                whichCmd = 2;
                break;
            default:
                whichCmd = 3;
        }
        if(!(Puzzle::invCmd(static_cast<Puzzle::Command>(path[path.size() - 1])) == c)) neighbours[whichCmd] = new Node(path+c, depth+1);
    }
}

Node::Node(std::string path, int depth) : path(std::move(path)), depth(depth){
    this->neighbours[0] = nullptr;//new Node();
    this->neighbours[1] = nullptr;//new Node();
    this->neighbours[2] = nullptr;//new Node();
    this->neighbours[3] = nullptr;//new Node();
}

Node::Node() :path("") {
    this->neighbours[0] = nullptr;
    this->neighbours[1] = nullptr;
    this->neighbours[2] = nullptr;
    this->neighbours[3] = nullptr;
}

Node *Node::getNeighbour(char c) {
    switch (c)
    {
        case 'L':
            return neighbours[0];
        case 'R':
            return neighbours[1];
        case 'U':
            return neighbours[2];
        case 'D':
            return neighbours[3];
        default:
            return nullptr;
    }
}
