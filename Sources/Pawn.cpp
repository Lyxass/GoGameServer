//
// Created by lyxas on 29/05/2020.
//

#include "../Header/Pawn.h"
Pawn::Pawn() {
    x = -1;
    y = -1;
    p = new Player("");
}


Pawn::Pawn(int x,int y, Player *p) {
    this->x = x;
    this->y = y;
    this->p = p;
}

Player Pawn::getPlayer() {
    return p;
}

int Pawn::getX() {
    return x;
}

int Pawn::getY() {
    return y;
}

void Pawn::setP(Player p) {
    this->p = p;
}

void Pawn::setX(int x) {
    this->x = x;
}

void Pawn::setY(int y) {
    this->y = y;
}