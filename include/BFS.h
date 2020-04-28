#ifndef FIFTHTEEN_BFS_H
#define FIFTHTEEN_BFS_H

#include "Strategy.h"

class BFS : public Strategy{
public:
    BFS(std::string checkingOrder);
    std::string explore(Graph* graph) override;
};

#endif //FIFTHTEEN_BFS_H
