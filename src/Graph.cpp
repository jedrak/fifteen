#include "../include/Graph.h"

Graph::Graph(Puzzle *puzzle) {
    this->puzzle = puzzle;
    this->root = new Node();
}
