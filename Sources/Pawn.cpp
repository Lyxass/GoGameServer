//
// Created by lyxas on 29/05/2020.
//

#include "../Header/Pawn.h"
Pawn::Pawn() {
    x = -1;
    y = -1;
    p = new Player("",'#',false);
}


Pawn::Pawn(int x,int y, Player *p) {
    this->x = x;
    this->y = y;
    this->p = p;
}

Player* Pawn::getPlayer() {
    return p;
}

int Pawn::getX() const {
    return x;
}

int Pawn::getY() const {
    return y;
}

void Pawn::setP(Player *p) {
    this->p = p;
}

void Pawn::setX(int x) {
    this->x = x;
}

void Pawn::setY(int y) {
    this->y = y;
}

bool operator==(Pawn  p1, Pawn  p2){
    return p1.getX() == p2.getX() && p1.getY() == p2.getY() && p1.getPlayer() == p2.getPlayer();
}

std::string Pawn::getString() {
    return "X : " + std::to_string(getX()) + " Y : "+ std::to_string(getY()) + p->getString();
}
