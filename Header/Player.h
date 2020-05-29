//
// Created by lyxas on 29/05/2020.
//

#ifndef GOGAMECPP_PLAYER_H
#define GOGAMECPP_PLAYER_H

#include "string"

class Player {
private:
    std::string pseudo;
public:
    Player(std::string pseudo);

    std::string getPseudo();
    void setPseudo(std::string pseudo);

};

bool operator==(Player p1,Player p2);

#endif //GOGAMECPP_PLAYER_H
