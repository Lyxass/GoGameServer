//
// Created by lyxas on 29/05/2020.
//

#ifndef GOGAMECPP_PAWN_H
#define GOGAMECPP_PAWN_H

#include "Player.h"


class Pawn {
private:
    int x;
    int y;
    Player *p;

public:
    Pawn();
    Pawn(int x, int y, Player *p);
    void setX(int x);
    void setY(int y);
    void setP(Player p);
    int getX();
    int getY();
    Player getPlayer();

};

bool operator==(Pawn const p1, Pawn const p2);


#endif //GOGAMECPP_PAWN_H
