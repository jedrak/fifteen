#ifndef FIFTHTEEN_GRAPH_H
#define FIFTHTEEN_GRAPH_H

#include "Node.h"

class Graph {
public:
    Node* root;
    Puzzle* puzzle;
    Graph(Puzzle* puzzle);
};

#endif //FIFTHTEEN_GRAPH_H
