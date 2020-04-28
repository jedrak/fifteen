#include <iostream>
#include "../include/Puzzle.h"
#include "../include/Graph.h"
#include "../include/BFS.h"
#include "../include/DFS.h"
#include "../include/Astar.h"

bool char_cmp(const char* a, const char* b, uint8_t lenght)
{
    for (int i = 0; i < lenght; i++) if (a[i] != b[i]) return false;
    return true;
}

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

int main(int argc, const char* argv[])
{
    Strategy* alg = nullptr;

    // Read the arguments
    if (argc < 6) {
        std::cerr << "Invalid argument count: " <<argc<<", expeced: 5" << std::endl;
        return -1;
    }

    /// argv[1] == Algorithm type
    if (char_cmp(argv[1], "bfs", 3))
    {
        /// argv[2] == Method "DRUL" .. itp
        alg = new BFS(argv[2]);
    }
    else if (char_cmp(argv[1], "dfs", 3))
    {
        /// argv[2] == Method "DRUL" .. itp
        alg = new DFS(argv[2]);
    }
    else if (char_cmp(argv[1], "astr", 4))
    {
        /// argv[2] == Method "manh" || "hamm"
        alg = new Astar(argv[2]);
    }
    else
    {
        std::cerr<<"Fail"<<std::endl;
        return -3;
    }

    /// argv[3] == Puzzle
    auto p = new Puzzle(argv[3]);
    
    auto graph = new Graph(p);
    std::string solution = alg->explore(graph);

    /// argv[4] == Solution File
    produceSolutionFile(argv[4], solution);
    /// argv[5] == Stats File
    produceStatFile(argv[5], alg->stats);

    return 0;
}
