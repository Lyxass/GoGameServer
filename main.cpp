#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "Header/Pawn.h"
#include "Header/Board.h"
#include "Header/Player.h"

using namespace std;

int main() {
    Board b = Board();
    Player j1 = Player("J1", "O");
    Player j2 = Player("J2", "X");

    /*b.setPawn(new Pawn(0,0,&j1));
    b.setPawn(new Pawn(0,1,&j1));
    b.setPawn(new Pawn(1,1,&j1));
    b.setPawn(new Pawn(1,2,&j1));
    b.setPawn(new Pawn(1,3,&j1));
    b.setPawn(new Pawn(2,3,&j1));

    printf("%s",b.getString().c_str());
    printf("\n");

    vector<Pawn*> chain = b.getChain(b.getPawn(0,0),new vector<Pawn*>());

    b.setPawn(new Pawn(0,2,&j2));
    b.setPawn(new Pawn(2,1,&j2));
    b.setPawn(new Pawn(2,2,&j2));
    b.setPawn(new Pawn(3,3,&j2));
    b.setPawn(new Pawn(2,4,&j2));
    b.setPawn(new Pawn(1,4,&j2));
    b.setPawn(new Pawn(0,3,&j2));

    printf("%s",b.getString().c_str());
    printf("\n");

    printf("%d\n",b.getLibertyOfChain(b.getChain(new Pawn(7,7,&j1),new vector<Pawn*>())).size());

    vector<Pawn*> chain2 = b.getChain(b.getPawn(0,8),new vector<Pawn*>());
    printf("%s\n",b.getLibertyOfChain(b.getChain(new Pawn(0,0,&j1),new vector<Pawn*>())).at(0)->getString().c_str());

    b.setPawn(new Pawn(1,0,&j2));
    printf("%s",b.getString().c_str());
    printf("\n");*/
    while (1) {
        int x, y;
        while (1) {
            printf("%s\n",b.getString().c_str());
            printf("J1 turn : ");
            scanf("%d,%d", &x, &y);
            if(x>=0 && x<=8 && y>=0 && y<= 8){
                break;
            }
            printf("Error, wrong Pattern or invalid input");
        }
        b.setPawn(new Pawn(x,y,&j1));

        while (1) {
            printf("%s\n",b.getString().c_str());
            printf("J2 turn : ");
            scanf("%d,%d", &x, &y);
            if(x>=0 && x<=8 && y>=0 && y<= 8){
                break;
            }
            printf("Error, wrong Pattern or invalid input");
        }
        b.setPawn(new Pawn(x,y,&j2));
    }


}