#ifndef FIFTHTEEN_DFS_H
#define FIFTHTEEN_DFS_H

#include "Strategy.h"

class DFS : public Strategy
{
public:
    DFS(std::string checkingOrder);
    std::string explore(Graph* graph) override;
};

#endif //FIFTHTEEN_DFS_H
