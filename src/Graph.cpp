//
// Created by jedra on 30.03.2020.
//

#include "../include/Graph.h"

Graph::Graph(Puzzle *puzzle) {
    this->puzzle = puzzle;
    this->root = new Node();
}
