#include <iostream>
#include "../include/Puzzle.h"
#include "../include/Graph.h"
#include "../include/BFS.h"
#include "../include/DFS.h"

void produceSolutionFile(const std::string& name, const std::string& solution)
{
    std::fstream file;
    file.open(name, std::ios::out);
    file<<solution.size()<<std::endl<<solution;
    file.close();
}

void produceStatFile(const std::string& name, Stats stats)
{
    std::fstream file;
    file.open(name, std::ios::out);
    file<<stats;
    file.close();
}




int main() {

    auto p = new Puzzle("../res/4x4_10_00001.txt");
    auto graph = new Graph(p);
    auto dfs = new DFS("DRLU");
    std::cout<<*p<<std::endl;
    std::string solution = dfs->explore(graph);
    std::cout<<solution<<" "<<solution.size()<<std::endl;
    p->processInput(solution);
    std::cout<<*p;
    produceSolutionFile("../sol/sol.txt", solution);
    produceStatFile("../sol/stats.txt", dfs->stats);
    std::cout<<dfs->stats.maxDepth;
    return 0;
}