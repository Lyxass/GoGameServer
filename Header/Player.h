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
    int pawnCaptured;
    bool isGuiClient;
public:
    Player(std::string pseudo, std::string symbol, bool isGuiClient);

    std::string getPseudo();
    void setPseudo(std::string pseudo);
    std::string getSymbol();
    void setSymbol(std::string s);
    std::string getString();
    void setPawnCaptured(int cpt);
    int getPawnCaptured();
    bool getIsGuiClient();
    void setIsGuiCLient(bool b);


};

bool operator==(Player p1,Player p2);

#endif //GOGAMECPP_PLAYER_H
