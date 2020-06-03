//
// Created by lyxas on 29/05/2020.
//

#include <iostream>
#include "../Header/Board.h"

using namespace std;


Board::Board() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            matrix[i][j] = Pawn(i, j, new Player("",'#',false));
        }
    }
    size = 9;
}

int Board::getSize() const {
    return size;
}

std::vector<Pawn *> Board::getLiberty(Pawn *p) {
    vector<Pawn *> res;
    if (p->getX() > 8 || p->getX() < 0 || p->getY() > 8 || p->getY() < 0) {
        throw invalid_argument("getLiberty : X and Y must be in interval [0,8]");
    }
    if (p->getX() - 1 >= 0) {
        if (getPawn(p->getX() - 1, p->getY())->getPlayer()->getSymbol() == '#') {
            res.push_back(getPawn(p->getX() - 1, p->getY()));
        }
    }
    if (p->getX() + 1 <= 8) {
        if (getPawn(p->getX() + 1, p->getY())->getPlayer()->getSymbol() == '#') {
            res.push_back(getPawn(p->getX() + 1, p->getY()));
        }
    }
    if (p->getY() - 1 >= 0) {
        if (getPawn(p->getX(), p->getY() - 1)->getPlayer()->getSymbol() == '#') {
            res.push_back(getPawn(p->getX(), p->getY() - 1));
        }
    }
    if (p->getY() + 1 <= 8) {
        if (getPawn(p->getX(), p->getY() + 1)->getPlayer()->getSymbol() == '#') {
            res.push_back(getPawn(p->getX(), p->getY() + 1));
        }
    }
    return res;
}

Pawn* Board::getPawn(int x, int y) {
    if (x < 0 || x > 8 || y < 0 || y > 8) {
        throw invalid_argument("getPawn : X and Y must be in interval [0,8]");
    }
    return &matrix[x][y];
}

bool Board::isValidMove(Pawn *p) {
    if (p->getX() < 0 || p->getX() > 8 || p->getY() < 0 || p->getY() > 8) {
        throw invalid_argument("isValidMove : X and Y must be in interval [0,8]");
    }
    if (!getPawn(p->getX(), p->getY())->getPlayer()->getPseudo().empty()) {
        return false;
    }
    manageIfPawnIsCaptured(p);
    return !getLiberty(p).empty();
}

void Board::setPawn(Pawn *p) {
    if (p->getX() < 0 || p->getX() > 8 || p->getY() < 0 || p->getY() > 8) {
        throw invalid_argument("setPawn : X and Y must be in interval [0,8]");
    }
    if (isValidMove(p)) {
        matrix[p->getX()][p->getY()] = *p;
    } else {
        throw runtime_error("Invalid Move");
    }
}

vector<Pawn *> Board::getChain(Pawn *p,vector<Pawn*> *res) {
    if (p->getX() < 0 || p->getX() > 8 || p->getY() < 0 || p->getY() > 8) {
        throw invalid_argument("getChain : X and Y must be in interval [0,8]");
    }
    if(p->getPlayer()->getSymbol() == '#'){
        return *res;
    }
    if(!existIn(*res,p)){
        res->push_back(p);
    }
    Pawn *tmp;
    if (p->getX() - 1 >= 0) {
        tmp = getPawn(p->getX() - 1, p->getY());
        if (p->getPlayer() == tmp->getPlayer()) {
            if (!existIn(*res, tmp)) {
                res->push_back(tmp);
                getChain(tmp,res);
            }
        }
    }
    if (p->getX() + 1 <= 8) {
        tmp = getPawn(p->getX() + 1, p->getY());
        if (p->getPlayer() == tmp->getPlayer()) {
            if (!existIn(*res, tmp)) {
                res->push_back(tmp);
                getChain(tmp,res);
            }
        }
    }
    if (p->getY() - 1 >= 0) {
        tmp = getPawn(p->getX(), p->getY() - 1);
        if (p->getPlayer() == tmp->getPlayer()) {
            if (!existIn(*res, tmp)) {
                res->push_back(tmp);
                getChain(tmp,res);
            }
        }
    }
    if (p->getY() + 1 <= 8) {
        tmp = getPawn(p->getX(), p->getY() + 1);
        if (p->getPlayer() == tmp->getPlayer()) {
            if (!existIn(*res, tmp)) {
                res->push_back(tmp);
                getChain(tmp,res);
            }
        }
    }
    return *res;
}

vector<Pawn *> Board::concatenate(std::vector<Pawn *> p1, std::vector<Pawn *> p2) {
    vector<Pawn *> res;
    for (int i = 0; i < p1.size(); ++i) {
        if (!existIn(res, p1.at(i))) {
            res.push_back(p1.at(i));
        }
    }
    for (int i = 0; i < p2.size(); ++i) {
        if (!existIn(res, p2.at(i))) {
            res.push_back(p2.at(i));
        }
    }
    return res;
}

bool Board::existIn(std::vector<Pawn *> p1, Pawn *p) {
    if (p->getX() < 0 || p->getX() > 8 || p->getY() < 0 || p->getY() > 8) {
        throw invalid_argument("existIn : X and Y must be in interval [0,8]");
    }
    for (int i = 0; i < p1.size(); ++i) {
        if (*p1.at(i) == *p) {
            return true;
        }
    }
    return false;
}

string Board::getString()  {
    string res;
    res = "";
    for (int j = 0; j < 9; ++j) {
        for (int i = 0; i < 8; ++i) {
             res += matrix[j][i].getPlayer()->getSymbol();
             res += "--";
        }
        res+= getPawn(j,8)->getPlayer()->getSymbol() ;
        res += "\n";
    }
    return res;
}

void Board::manageIfPawnIsCaptured(Pawn *p){
    if(p->getX()-1 >=0){
        Pawn *tmp;
        tmp = getPawn(p->getX()-1,p->getY());
        if(tmp->getPlayer() != p->getPlayer() && tmp->getPlayer()->getSymbol() != '#'){
            vector<Pawn*> libertyChain = getLibertyOfChain(getChain(tmp,new vector<Pawn*>()));
            if(libertyChain.size() == 1 && p->getY() == libertyChain.at(0)->getY() && p->getX() == libertyChain.at(0)->getX()){
                capturePawn(getChain(tmp,new vector<Pawn*>()),p->getPlayer());
            }
        }
    }
    if(p->getX()+1 <=8){
        Pawn *tmp;
        tmp = getPawn(p->getX()+1,p->getY());
        if(tmp->getPlayer() != p->getPlayer() && tmp->getPlayer()->getSymbol() != '#'){
            vector<Pawn*> libertyChain = getLibertyOfChain(getChain(tmp,new vector<Pawn*>()));
            if(libertyChain.size() == 1 && p->getY() == libertyChain.at(0)->getY() && p->getX() == libertyChain.at(0)->getX()){
                capturePawn(getChain(tmp,new vector<Pawn*>()),p->getPlayer());
            }
        }
    }
    if(p->getY()-1 >=0){
        Pawn *tmp;
        tmp = getPawn(p->getX(),p->getY()-1);
        if(tmp->getPlayer() != p->getPlayer() && tmp->getPlayer()->getSymbol() != '#'){
            vector<Pawn*> libertyChain = getLibertyOfChain(getChain(tmp,new vector<Pawn*>()));
            if(libertyChain.size() == 1 && p->getY() == libertyChain.at(0)->getY() && p->getX() == libertyChain.at(0)->getX()){
                capturePawn(getChain(tmp,new vector<Pawn*>()),p->getPlayer());
            }
        }
    }if(p->getY()+1 <=8){
        Pawn *tmp;
        tmp = getPawn(p->getX(),p->getY()+1);
        if(tmp->getPlayer() != p->getPlayer() && tmp->getPlayer()->getSymbol() != '#'){
            vector<Pawn*> libertyChain = getLibertyOfChain(getChain(tmp,new vector<Pawn*>()));
            if(libertyChain.size() == 1 && p->getY() == libertyChain.at(0)->getY() && p->getX() == libertyChain.at(0)->getX()){
                capturePawn(getChain(tmp,new vector<Pawn*>()),p->getPlayer());
            }
        }
    }
}

std::vector<Pawn*> Board::getLibertyOfChain(std::vector<Pawn*> chain){
    std::vector<Pawn*> res;
    for (int i = 0; i < chain.size(); ++i) {
        res = concatenate(res,getLiberty(chain.at(i)));
    }
    return res;
}

void Board::capturePawn(std::vector<Pawn *> chain, Player *p) {
    for (int i = 0; i < chain.size(); ++i) {
        matrix[chain.at(i)->getX()][chain.at(i)->getY()] = Pawn(chain.at(i)->getX(),chain.at(i)->getY(),new Player("",'#',false));
        p->setPawnCaptured(p->getPawnCaptured()+1);
    }
}

void Board::getStringForGui(char tab[2048]) {
    for (int i = 0; i <2048 ; ++i) {

        tab[i] = 0;
    }
    for (int i = 0; i < 9*9; ++i) {
        tab[i] += matrix[i/9][i%9].getPlayer()->getSymbol();
    }
    printf("%s\n",tab);



}
