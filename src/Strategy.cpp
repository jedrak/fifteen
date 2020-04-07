//
// Created by jedra on 30.03.2020.
//
#include <utility>
#include <fstream>
#include "../include/Strategy.h"

Strategy::Strategy(std::string checkingOrder, std::string strategyName) : checkingOrder(std::move(checkingOrder)), strategyName(std::move(strategyName)){
    queue = std::deque<Node*>();
    stats = Stats();
}

void Stats::clear() {
    numberOfMoves = 0;
    numberOfVisited = 0;
    numberOfProcessed = 0;
    maxDepth = 0;
    time = 0;
}

std::ostream &operator<<(std::ostream &os, const Stats &data) {
    os<<data.numberOfMoves<<std::endl;
    os<<data.numberOfVisited<<std::endl;
    os<<data.numberOfProcessed<<std::endl;
    os<<data.maxDepth<<std::endl;
    os<<data.time<<std::endl;
    return os;
}
