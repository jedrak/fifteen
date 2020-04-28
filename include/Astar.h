#ifndef FIFTHTEEN_ASTAR_H
#define FIFTHTEEN_ASTAR_H

#include "Strategy.h"

class Astar : public Strategy
{
public:
    Astar(std::string method);
    std::string explore(Graph* graph) override;
};

#endif //FIFTHTEEN_ASTAR_H
