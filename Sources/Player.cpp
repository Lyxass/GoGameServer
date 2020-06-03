//
// Created by lyxas on 29/05/2020.
//

#include "../Header/Player.h"

Player::Player(std::string pseudo, char symbol, bool isGuiClient) {
    this->pseudo = pseudo;
    this->symbol = symbol;
    pawnCaptured = 0;
    this->isGuiClient = isGuiClient;
}

std::string Player::getPseudo() {
    return pseudo;
}

void Player::setPseudo(std::string pseudo) {
    this->pseudo = pseudo;
}

char Player::getSymbol() {
    return symbol;
}

void Player::setSymbol(char s) {
    this->symbol = s;
}

bool operator==(Player p1,Player p2){
   return p1.getPseudo() == p2.getPseudo() && p1.getSymbol() == p2.getSymbol();
}

std::string Player::getString() {
    return "Pseudo : " + pseudo + " Symbol : "+ symbol;
}

void Player::setPawnCaptured(int cpt) {
    pawnCaptured = cpt;
}

int Player::getPawnCaptured() {
    return pawnCaptured;
}

bool Player::getIsGuiClient() {return isGuiClient;}

void Player::setIsGuiCLient(bool b) {isGuiClient = b;}