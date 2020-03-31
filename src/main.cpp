#include <iostream>
#include "../include/Puzzle.h"
#include "../include/Graph.h"
#include "../include/BFS.h"

void produceSolutionFile(const std::string& name, const std::string& solution) {
    std::fstream file;
    file.open(name, std::ios::out);
    file<<solution.size()<<std::endl<<solution;
    file.close();
}


int main() {

    auto p = new Puzzle("../res/4x4_10_01001.txt");
    auto graph = new Graph(p);
    auto bfs = new BFS("LDUR");
    std::cout<<*p<<std::endl;
    std::string solution = bfs->explore(graph);
    p->processInput(solution);
    std::cout<<*p<<p->isSolved();
    produceSolutionFile("../sol/4x4_10_01001_bfs_ldur_sol.txt", solution);
    return 0;
}