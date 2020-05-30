//
// Created by lyxas on 29/05/2020.
//

#include "../Header/Player.h"

Player::Player(std::string pseudo, std::string symbol) {
    this->pseudo = pseudo;
    this->symbol = symbol;
}

std::string Player::getPseudo() {
    return pseudo;
}

void Player::setPseudo(std::string pseudo) {
    this->pseudo = pseudo;
}

std::string Player::getSymbol() {
    return symbol;
}

void Player::setSymbol(std::string s) {
    this->symbol = s;
}

bool operator==(Player p1,Player p2){
   return p1.getPseudo() == p2.getPseudo() && p1.getSymbol() == p2.getSymbol();
}

std::string Player::getString() {
    return "Pseudo : " + pseudo + " Symbol : "+ symbol;
}
