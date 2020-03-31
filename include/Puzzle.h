//
// Created by jedra on 29.03.2020.
//

#ifndef FIFTHTEEN_PUZZLE_H
#define FIFTHTEEN_PUZZLE_H


#include <sstream>
#include <fstream>


class Puzzle {

    short position = 15;
    short w = 4;
    short h = 4;
    short* state;
public:
    enum Command{
        Left = 'L',
        Right = 'R',
        Up = 'U',
        Down = 'D',
        Zero = 'Z'
    };
    Puzzle();
    Puzzle(short w, short h);
    Puzzle(std::string);
    Puzzle(Puzzle*);
    ~Puzzle();
    static Command invCmd(Command cmd);
    static std::string invChain(std::string input);

    friend std::ostream& operator<< (std::ostream& os, const Puzzle& data);
    bool isPossible(Command command);
    short* move(Command command);
    void processInput(const std::string& input);
    void revertInput(const std::string& input);
    std::string possibleMoves();
    bool isSolved();
};


#endif //FIFTHT&EEN_PUZZLE_H
