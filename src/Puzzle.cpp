//
// Created by jedra on 29.03.2020.
//

#include <iostream>

#include "../include/Puzzle.h"

std::ostream& operator<<(std::ostream &os, const Puzzle &data) {
    os<<std::endl;
    //os<<" "<<data.w<<"  "<<data.h;
    for(int i = 0; i < data.w*data.h; i++)
    {
        if(i % data.w == 0) {
            os<<"\n";
        }
        if(data.state[i]/10 < 1) os<<" "; // to make sure it always displays pretty
        os<<data.state[i]<< " ";
    }
    //os<<std::endl<<data.position<<std::endl;
    return os;
}


bool Puzzle::isPossible(Puzzle::Command command) {
    bool result = false;
    switch(command){
        case Left:
            result = position % w != 0;
            break;
        case Right:
            result = position % w != w-1;
            break;
        case Up:
            result = position / h != 0;
            break;
        case Down:
            result = position / h != h-1;
            break;
    }
    return result;
}

short* Puzzle::move(Puzzle::Command command) {
    if(isPossible(command)){
        switch(command){
            case Left:
                state[position] = state[position-1];
                position--;
                state[position] = 0;
                break;
            case Right:
                state[position] = state[position+1];
                position++;
                state[position] = 0;
                break;
            case Up:
                state[position] = state[position-w];
                position-=w;
                state[position] = 0;
                break;
            case Down:
                state[position] = state[position+w];
                position+=w;
                state[position] = 0;
                break;
            case Zero:
                break;
        }

    }
    return state;
}

void Puzzle::processInput(const std::string& input) {
    for(char c : input){
        move(static_cast<Puzzle::Command>(c));

    }

}

std::string Puzzle::possibleMoves() {
    std::string result;
    const Command Commands[] = {Command::Left, Command::Right, Command::Up, Command::Down};
    for(auto cmd : Commands){
        if(isPossible(cmd)) result.push_back(cmd);
    }
    return result;
}

Puzzle::Puzzle(std::string path) {
    std::fstream file;
    file.open(path);
    if(file.good())
    {
        file>>w>>h;
        state = new short[w*h];
        short i=-1, buff;
        while(file>>state[++i]) if(state[i] == 0) position = i;
    }
}

Puzzle::Puzzle() {
    state = new short[16];
    for(short i = 0; i<16; i++){
        state[i] = i+1;
    }
    state[position] = 0;
}

bool Puzzle::isSolved() {
    bool result = true;
    Puzzle p = Puzzle(w, h);
    if(position != p.position) return false;
    for(int i = 0; i<w*h; i++)
    {
        if(state[i] != p.state[i])
        {
            return false;
        }
    }


    return true;
}

Puzzle::Puzzle(short w, short h) : w(w), h(h), position((w*h)-1){
    state = new short[w*h];
    for(short i = 0; i<w*h; i++){
        state[i] = i+1;
    }
    state[position] = 0;

}

Puzzle::Puzzle(Puzzle * p) : w(p->w), h(p->h), position(p->position) {
    state = new short[w*h];
    for(int i=0; i< w*h; i++)
        state[i] = p->state[i];
}

Puzzle::~Puzzle() {
    delete state;
}

Puzzle::Command Puzzle::invCmd(Puzzle::Command cmd) {
    Puzzle::Command result;
    switch (cmd){
        case Left:
            result = Right;
            break;
        case Right:
            result = Left;
            break;
        case Up:
            result = Down;
            break;
        case Down:
            result = Up;
            break;
        default:
            result = Zero;
            break;
    }
    return result;
}

std::string Puzzle::invChain(std::string input) {
    if(input.empty()) return "";
    std::string result;
    for(int i=input.size()-1; i>=0; i--)
    {
        result.push_back(Puzzle::invCmd(static_cast<Puzzle::Command>(input[i])));
    }

    return result;
}

void Puzzle::revertInput(const std::string &inp) {
    std::string invPath = Puzzle::invChain(inp);
    processInput(invPath);
}




