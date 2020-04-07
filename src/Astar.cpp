//
// Created by jaro on 02.04.2020.
//

#include <utility>
#include <chrono>
#include <list>
#include "../include/Astar.h"

Astar::Astar(std::string method) : Strategy(std::move(method), "astr") {}

/*struct NodeComparator
{
    bool operator ()(const Node* node1, const Node* node2)
    {
        return node1->h < node2->h;
    }
};*/

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
    queue.clear();
    queue.push_front(graph->root);
    Node* toProcess = graph->root;

    unsigned int (*heuristic)(Puzzle*);
    if (checkingOrder == "manh")
        heuristic = &manhattanDistance;
    else /*if(checkingOrder == "hamm")*/
        heuristic = &hammingDistance;

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
            Node* node = nullptr;
            std::list<Node*> temp;

            for(auto c : "LURD") {
                node = toProcess->getNeighbour(c);
                if(node && node->depth < 12)
                {
                    graph->puzzle->revertInput(node->path);
                    graph->puzzle->processInput(node->path);
                    node->h = heuristic(graph->puzzle);
                    graph->puzzle->revertInput(node->path);
                    temp.push_back(node);
                    stats.numberOfVisited++;
                }
            }

//            temp.sort(NodeComparator());

            while(!temp.empty())
            {
                queue.push_front(temp.back());
                temp.pop_back();
            }
        }
    }

    graph->puzzle->revertInput(toProcess->path);

    stats.numberOfMoves = toProcess->path.size();

    auto end = std::chrono::steady_clock::now();
    stats.time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    return toProcess->path;
}
