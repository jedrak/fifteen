#ifndef FIFTHTEEN_STRATEGY_H
#define FIFTHTEEN_STRATEGY_H

#include <queue>
#include <utility>
#include "Node.h"
#include "Graph.h"

struct Stats{
    int numberOfMoves = 0;
    int numberOfVisited = 0;
    int numberOfProcessed = 0;
    int maxDepth = 0;
    float time = 0;
    void clear();
    friend std::ostream& operator<< (std::ostream& os, const Stats& data);
};

class Strategy
{
public:
    unsigned int max_depth = 20;
    std::deque<Node*> queue;
    std::string checkingOrder;
    std::string strategyName;
    Stats stats;

    Strategy(std::string checkingOrder, std::string strategyName);

    virtual std::string explore(Graph* graph) { throw -1; };
};

#endif //FIFTHTEEN_STRATEGY_H
