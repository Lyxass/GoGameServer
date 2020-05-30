//
// Created by lyxas on 29/05/2020.
//

#include <iostream>
#include "../Header/Board.h"

using namespace std;


Board::Board() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            matrix[i][j] = Pawn(i, j, new Player("","#"));
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
        throw invalid_argument("X and Y must be in interval [0,8]");
    }
    if (p->getX() - 1 >= 0) {
        if (p->getPlayer()->getPseudo() != getPawn(p->getX() - 1, p->getY())->getPlayer()->getPseudo()) {
            res.push_back(getPawn(p->getX() - 1, p->getY()));
        }
    }
    if (p->getX() + 1 <= 8) {
        if (p->getPlayer()->getPseudo() != getPawn(p->getX() + 1, p->getY())->getPlayer()->getPseudo()) {
            res.push_back(getPawn(p->getX() + 1, p->getY()));
        }
    }
    if (p->getY() - 1 >= 0) {
        if (p->getPlayer()->getPseudo() != getPawn(p->getX(), p->getY() - 1)->getPlayer()->getPseudo()) {
            res.push_back(getPawn(p->getX(), p->getY() - 1));
        }
    }
    if (p->getY() + 1 <= 8) {
        if (p->getPlayer()->getPseudo() != getPawn(p->getX(), p->getY() + 1)->getPlayer()->getPseudo()) {
            res.push_back(getPawn(p->getX(), p->getY() + 1));
        }
    }
    return res;
}

Pawn *Board::getPawn(int x, int y) {
    if (x < 0 || x > 8 || y < 0 || y > 8) {
        throw invalid_argument("X and Y must be in interval [0,8]");
    }
    return &matrix[x][y];
}

bool Board::isValidMove(Pawn *p) {
    if (p->getX() < 0 || p->getX() > 8 || p->getY() < 0 || p->getY() > 8) {
        throw invalid_argument("X and Y must be in interval [0,8]");
    }
    if (!getPawn(p->getX(), p->getY())->getPlayer()->getPseudo().empty()) {
        return false;
    }
    return !getLiberty(p).empty();
}

void Board::setPawn(Pawn *p) {
    if (isValidMove(p)) {
        matrix[p->getX()][p->getY()] = *p;
    } else {
        throw runtime_error("Invalid Move");
    }
}

vector<Pawn *> Board::getChain(Pawn *p,vector<Pawn*> *res) {
    if(!existIn(*res,p)){
        res->push_back(p);
    }
    Pawn *tmp;
    if (p->getX() - 1 >= 0) {
        tmp = getPawn(p->getX() - 1, p->getY());
        if (p->getPlayer()->getPseudo() == tmp->getPlayer()->getPseudo()) {
            if (!existIn(*res, tmp)) {
                res->push_back(tmp);
                getChain(tmp,res);
            }
        }
    }
    if (p->getX() + 1 <= 8) {
        tmp = getPawn(p->getX() + 1, p->getY());
        if (p->getPlayer()->getPseudo() == tmp->getPlayer()->getPseudo()) {
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
        if (p->getPlayer()->getPseudo() == tmp->getPlayer()->getPseudo()) {
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

Board::Board(int size) {
    this->size = size;

}

bool Board::existIn(std::vector<Pawn *> p1, Pawn *p) {
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
             res += getPawn(j,i)->getPlayer()->getSymbol() + "--";
        }
        res+= getPawn(j,8)->getPlayer()->getSymbol() + "\n";
    }
    return res;
}


