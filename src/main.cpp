#include <iostream>
#include "../include/Puzzle.h"
#include "../include/Graph.h"
#include "../include/BFS.h"

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

    auto p = new Puzzle("../res/4x4_08_00268.txt");
    auto graph = new Graph(p);
    auto bfs = new BFS("LDUR");
    std::cout<<*p<<std::endl;
    std::string solution = bfs->explore(graph);
    p->processInput(solution);
    std::cout<<*p<<p->isSolved();
    produceSolutionFile("../sol/sol.txt", solution);
    produceStatFile("../sol/stats.txt", bfs->stats);
    return 0;
}