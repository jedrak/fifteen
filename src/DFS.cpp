#include <utility>
#include <chrono>
#include <iostream>
#include "../include/DFS.h"

DFS::DFS(std::string checkingOrder) : Strategy(std::move(checkingOrder),"dfs") {}

std::string DFS::explore(Graph* graph) {
    auto start = std::chrono::steady_clock::now();
    stats.clear();
    queue.clear();
    queue.push_back(graph->root);
    Node* toProcess = graph->root;
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
            for(auto c : checkingOrder)
            {
                if(toProcess->getNeighbour(c) && toProcess->getNeighbour(c)->depth < max_depth)
                {
                    queue.push_back(toProcess->getNeighbour(c));
                    stats.numberOfVisited++;
                }
            }
        }
    }
    stats.numberOfMoves = toProcess->path.size();
    auto end = std::chrono::steady_clock::now();
    stats.time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return toProcess->path;
}
