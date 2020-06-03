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

    std::vector<Pawn*> concatenate(std::vector<Pawn*> p1,std::vector<Pawn*> p2);
    void manageIfPawnIsCaptured(Pawn *p);
    void capturePawn(std::vector<Pawn*> chain,Player *p);

public:
    std::vector<Pawn*> getLibertyOfChain(std::vector<Pawn*> chain);
    bool existIn(std::vector<Pawn*> p1, Pawn* p);
    Board();
    int getSize() const;
    void setPawn(Pawn *p);
    Pawn* getPawn(int x, int y);

    bool isValidMove(Pawn *p);
    std::vector<Pawn*> getLiberty(Pawn *P);

    std::vector<Pawn*> getChain(Pawn *p,std::vector<Pawn*> *res);
    std::string getString();
    void getStringForGui(char tab[2048]);


};

std::ostream &operator<<(std::ostream &flux, const char *board);
#endif //GOGAMECPP_BOARD_H
