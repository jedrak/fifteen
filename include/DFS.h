//
// Created by jedra on 31.03.2020.
//

#ifndef FIFTHTEEN_DFS_H
#define FIFTHTEEN_DFS_H


#include "Strategy.h"

class DFS : public Strategy
{
public:
    DFS(std::string checkingOrder);
    std::string explore(Graph* graph);
};


#endif //FIFTHTEEN_DFS_H
