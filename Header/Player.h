//
// Created by lyxas on 29/05/2020.
//

#ifndef GOGAMECPP_PLAYER_H
#define GOGAMECPP_PLAYER_H

#include "string"

class Player {
private:
    std::string pseudo;
    std::string symbol;
public:
    Player(std::string pseudo, std::string symbol);

    std::string getPseudo();
    void setPseudo(std::string pseudo);
    std::string getSymbol();
    void setSymbol(std::string s);
    std::string getString();

};

bool operator==(Player p1,Player p2);

#endif //GOGAMECPP_PLAYER_H
