//
// Created by lyxas on 29/05/2020.
//

#include "../Header/Board.h"

using namespace std;

int Board::getSize() {
    return size;
}

Board::Board() {
    for (int i = 0; i < ; ++i) {
        for (int j = 0; j < ; ++j) {
            matrix[i][j] = Pawn(i,j,new Player(""));
        }
    }
    size = 9;
}

std::vector<Pawn> Board::getLiberty(Pawn *p) {
    vector<Pawn> res;
    if(p->getX()>8 || p->getX()<0 || p->getY()>8 || p->getY()<0){
        throw invalid_argument("X and Y must be in interval [0,8]");
    }
    if(p->getX()-1 >0){
        if(p->getPlayer().getPseudo() != getPawn(p->getX()-1,p->getY()).getPlayer().getPseudo()){
            res.push_back(getPawn(p->getX()-1,p->getY()));
        }
    }
    if(p->getX()+1 >0){
        if(p->getPlayer().getPseudo() != getPawn(p->getX()+1,p->getY()).getPlayer().getPseudo()){
            res.push_back(getPawn(p->getX()+1,p->getY()));
        }
    }
    if(p->getY()-1 >0){
        if(p->getPlayer().getPseudo() != getPawn(p->getX(),p->getY()-1).getPlayer().getPseudo()){
            res.push_back(getPawn(p->getX(),p->getY()-1));
        }
    }
    if(p->getY()+1 >0){
        if(p->getPlayer().getPseudo() != getPawn(p->getX(),p->getY()+1).getPlayer().getPseudo()){
            res.push_back(getPawn(p->getX(),p->getY()+1));
        }
    }
    return res;
}

Pawn Board::getPawn(int x, int y) {
    if(x<0 || x>8 || y<0 || y>8){
        throw invalid_argument("X and Y must be in interval [0,8]");
    }
    return matrix[x][y];
}

bool Board::isValidMove(Pawn *p) {
    if(p->getX()<0 || p->getX()>8 || p->getY()<0 || p->getY()>8){
        throw invalid_argument("X and Y must be in interval [0,8]");
    }
    if(getPawn(p->getX(),p->getY()).getPlayer().getPseudo() !=""){
        return false;
    }
    if(getLiberty(p).size() == 0){
        return false;
    }
    return true;
}

void Board::setPawn(Pawn *p) {
    if(isValidMove(p)){
        matrix[p->getX()][p->getY()] = *p;
    }
    else{
        throw runtime_error("Invalid Move");
    }
}