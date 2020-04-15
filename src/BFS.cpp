//
// Created by jedra on 30.03.2020.
//

#include <iostream>
#include <utility>
#include <chrono>
#include "../include/BFS.h"

BFS::BFS(std::string checkingOrder) : Strategy(std::move(checkingOrder),"bfs") {}

std::string BFS::explore(Graph* graph) {
    auto start = std::chrono::steady_clock::now();
    stats.clear();
    queue.clear();
    queue.push_back(graph->root);
    Node* toProcess = graph->root;
    while(!graph->puzzle->isSolved())
    {
        graph->puzzle->revertInput(toProcess->path);
        toProcess = queue.front();
        stats.numberOfProcessed++;
        if(stats.maxDepth < toProcess->depth) stats.maxDepth = toProcess->depth;
        queue.pop_front();
        graph->puzzle->processInput(toProcess->path);
        toProcess->initNeighbours(graph->puzzle);
        if(!toProcess->visited)
        {
            toProcess->visited = true;
            for(auto c : checkingOrder)
            {
                if (toProcess->getNeighbour(c))
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
    stats.time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return toProcess->path;
}
