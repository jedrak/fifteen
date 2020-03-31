//
// Created by jedra on 30.03.2020.
//
#include <utility>
#include <fstream>
#include "../include/Strategy.h"

Strategy::Strategy(std::string checkingOrder, std::string strategyName) : checkingOrder(std::move(checkingOrder)), strategyName(std::move(strategyName)){
    queue = std::deque<Node*>();
}


