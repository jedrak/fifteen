//
// Created by jedra on 30.03.2020.
//

#ifndef FIFTHTEEN_STRATEGY_H
#define FIFTHTEEN_STRATEGY_H

#include <queue>
#include <utility>
#include "Node.h"
#include "Graph.h"

class Strategy
{
public:
    std::deque<Node*> queue;
    std::string checkingOrder;
    std::string strategyName;
    Strategy(std::string checkingOrder, std::string strategyName);

    virtual std::string explore(Graph* graph) = 0;
};




#endif //FIFTHTEEN_STRATEGY_H
