//
// Created by jaro on 02.04.2020.
//

#include <utility>
#include <chrono>
#include <list>
#include "../include/Astar.h"

Astar::Astar(std::string method) : Strategy(std::move(method), "astr") {}

unsigned int hammingDistance(Puzzle* puzzle) {
    unsigned int misplaced = 0;
    const Puzzle solved = Puzzle(puzzle->w, puzzle->h);

    for(int i = 0; i<puzzle->w*puzzle->h; i++)
    {
        if(puzzle->state[i] != solved.state[i])
        {
            misplaced++;
        }
    }

    return misplaced;
}

unsigned int manhattanDistance(Puzzle* puzzle) {
    unsigned int sum = 0;

    for(int i = 0; i<puzzle->w*puzzle->h; i++)
    {
        if(puzzle->state[i] && puzzle->state[i] != i+1)
        {
            int temp = abs(puzzle->state[i] - (i + 1));
            sum += temp / puzzle->h + temp % puzzle->h;
        }
    }

    return sum;
}

std::string Astar::explore(Graph *graph) {
    auto start = std::chrono::steady_clock::now();

    stats.clear();
    std::list<Node*> list;
    list.push_front(graph->root);

    Node* toProcess = graph->root;

    unsigned int (*heuristic)(Puzzle*);
    if (checkingOrder == "manh")
        heuristic = &manhattanDistance;
    else /*if(checkingOrder == "hamm")*/
        heuristic = &hammingDistance;

    Node* node = nullptr;
    std::string string("LURD"), ch("L");

    while(!graph->puzzle->isSolved())
    {
        graph->puzzle->revertInput(toProcess->path);
        toProcess = list.front();
        list.pop_front();
        stats.numberOfProcessed++;
        if(stats.maxDepth < toProcess->depth) stats.maxDepth = toProcess->depth;
        graph->puzzle->processInput(toProcess->path);
        toProcess->initNeighbours(graph->puzzle);
        if(!toProcess->visited)
        {
            toProcess->visited = true;

            for(auto c : string) {
                node = toProcess->getNeighbour(c);
                if(node && node->depth < 12)
                {
                    ch[0] = c;
                    graph->puzzle->processInput(ch);
                    node->h = heuristic(graph->puzzle);
                    graph->puzzle->revertInput(ch);
                    list.push_front(node);
                    stats.numberOfVisited++;
                }
            }

            list.sort([](const Node* node1, const Node* node2) {
                return node1->h + node1->depth < node2->h + node2->depth;
            });
        }
    }

    graph->puzzle->revertInput(toProcess->path);

    stats.numberOfMoves = toProcess->path.size();

    auto end = std::chrono::steady_clock::now();
    stats.time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    return toProcess->path;
}
