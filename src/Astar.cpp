//
// Created by jaro on 02.04.2020.
//

#include <utility>
#include <chrono>
#include <iostream>
#include "../include/Astar.h"
#include <string>

Astar::Astar(std::string method) : Strategy(std::move(method), "astr") {}

std::string Astar::explore(Graph *graph) {
    auto start = std::chrono::steady_clock::now();

    stats.clear();
    queue.clear();
    queue.push_back(graph->root);
    Node* toProcess =  graph->root;

    while(!graph->puzzle->isSolved())
    {
        graph->puzzle->revertInput(toProcess->path);

        toProcess = queue.back();

        stats.numberOfProcessed++;

        if(stats.maxDepth < toProcess->depth) stats.maxDepth = toProcess->depth;

        queue.pop_back();

        graph->puzzle->processInput(toProcess->path);

        toProcess->initNeighbours(graph->puzzle);

        if(!toProcess->visited)
        {
            toProcess->visited = true;
            for(auto c : checkingOrder){
                if(toProcess->getNeighbour(c) && toProcess->getNeighbour(c)->depth< 12)
                {
                    queue.push_back(toProcess->getNeighbour(c));
                    stats.numberOfVisited++;
                }
            }
        }
    }

    graph->puzzle->revertInput(toProcess->path);

    stats.numberOfMoves = toProcess->path.size();

    auto end = std::chrono::steady_clock::now();
    stats.time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    return toProcess->path;
}
