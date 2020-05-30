#include "stdio.h"
#include "stdlib.h"
#include <cassert>
#include "Header/Pawn.h"
#include "Header/Board.h"
#include "Header/Player.h"

using namespace std;

int main(){
    Board b = Board(9);

    printf(b.getString().c_str());
    printf("\n");
    Player j1 = Player("J1","O");
    Player j2 = Player("J2","X");

    b.setPawn(new Pawn(0,0,&j1));
    printf(b.getString().c_str());
    printf("\n");

    b.setPawn(new Pawn(0,1,&j1));
    b.setPawn(new Pawn(1,1,&j1));
    b.setPawn(new Pawn(1,2,&j1));
    b.setPawn(new Pawn(1,3,&j1));
    b.setPawn(new Pawn(2,3,&j1));

    printf(b.getString().c_str());
    printf("\n");

    assert(b.getLiberty(new Pawn(0,0,&j1)).size() == 1);
    assert(b.getLiberty(new Pawn(1,1,&j1)).size() == 2);
    assert(b.getLiberty(new Pawn(2,3,&j1)).size() == 3);

    printf("%zu\n",b.getChain(new Pawn(1,1,&j1),new vector<Pawn*>()).size());

    Board b2 = Board(9);
    b2.setPawn(new Pawn(0,0,&j1));
    b2.setPawn(new Pawn(0,1,&j1));
    b2.setPawn(new Pawn(1,1,&j1));

    b2.setPawn(new Pawn(1,3,&j1));
    b2.setPawn(new Pawn(2,3,&j1));

    printf("%zu\n",b2.getChain(new Pawn(1,1,&j1),new vector<Pawn*>()).size());
    printf("%zu\n",b2.getChain(new Pawn(1,3,&j1),new vector<Pawn*>()).size());



    /*vector<Pawn*> tab;
    tab.push_back(new Pawn(1,1,&j1));
    tab.push_back(new Pawn(0,1,&j1));

    printf("%d\n",b.existIn(tab,new Pawn(1,1,&j1)));
    printf("%d\n",b.existIn(tab,new Pawn(0,1,&j1)));
    printf("%d\n",b.existIn(tab,new Pawn(4,1,&j1)));
    printf("%d\n",j1==j1);

    Player j3 = Player("J1","O");

    printf("%d\n",new Pawn(1,1,&j1)==new Pawn(1,1,&j1));
    printf("%d\n",Pawn(1,1,&j1) == Pawn(1,1,&j1));*/








}