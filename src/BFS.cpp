//
// Created by jedra on 30.03.2020.
//

#include <iostream>
#include <utility>
#include "../include/BFS.h"

std::string BFS::explore(Graph* graph) {
    queue.clear();
    queue.push_back(graph->root);
    Node* toProcess = graph->root;
    //auto* buff = new Puzzle(graph->puzzle);//not good
    //graph.root->visited = true;
    while(!graph->puzzle->isSolved()){

        graph->puzzle->revertInput(toProcess->path);
        //std::cout<<*graph->puzzle<<Puzzle::invChain(toProcess->path);
        toProcess = queue.front();
        queue.pop_front();
        graph->puzzle->processInput(toProcess->path);
        toProcess->initNeighbours(graph->puzzle);
        for(auto c : checkingOrder){
            if(toProcess->getNeighbour(c)) queue.push_back(toProcess->getNeighbour(c));
        }

        //std::cout<<toProcess->path<<std::endl;

    }
    graph->puzzle->revertInput(toProcess->path);
    return toProcess->path;
}

BFS::BFS(std::string checkingOrder) : Strategy(std::move(checkingOrder),"bfs") {}
