//
// Created by lyxas on 29/05/2020.
//

#ifndef GOGAMECPP_BOARD_H
#define GOGAMECPP_BOARD_H

#include "Pawn.h"
#include <vector>
#include "stdexcept"

class Board {
private:
    Pawn matrix[9][9];
    int size;

    std::vector<Pawn> concatenate(std::vector<Pawn> p1,std::vector<Pawn> p2);
    bool existIn(std::vector<Pawn> p1, Pawn p);
public:
    Board();
    Board(int size);
    int getSize();
    void setPawn(Pawn *p);
    Pawn getPawn(int x,int y);

    bool isValidMove(Pawn *p);
    std::vector<Pawn> getLiberty(Pawn *P);

    std::vector<Pawn> getChain(Pawn *p);

};


#endif //GOGAMECPP_BOARD_H
