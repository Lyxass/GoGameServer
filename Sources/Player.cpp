//
// Created by lyxas on 29/05/2020.
//

#include "../Header/Player.h"

std::string Player::getPseudo() {
    return pseudo;
}

void Player::setPseudo(std::string pseudo) {
    this->pseudo = pseudo;
}

Player::Player(std::string pseudo) {
    this->pseudo = pseudo;
}