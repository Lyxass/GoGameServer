/* Socket - ServeurUDP - Mode Datagramme */

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <stdexcept>
#include <iostream>
#include "Header/Player.h"
#include "Header/Pawn.h"
#include "Header/Board.h"
#include <string>

#define UDP_port_S 8000

using namespace std;

std::string prepareMessage(std::string board, Player *j1, Player *j2);

void playerTurn(Board *b, Player *pWhoPlay, Player *otherPlayer, int sock_S, sockaddr_in sa_j1, sockaddr_in sa_j2,
                unsigned int taille_sa, int *nbPlayerWantTofinish);

void sendBoardTo(Board *b, Player *pWhoPlay, Player *otherPlayer, int sock_S, sockaddr_in sa_client, bool isGuiClient,
                 unsigned int taille_sa);
void stringToCharTab(string str,char res[2048]);

int main() {
    int sock_S;

    char message[2048];
    int nbPlayerWantTofinish = 0;

    struct sockaddr_in sa_S, sa_j1, sa_j2;

    unsigned int taille_sa;

    /* creation socket Serveur*/
    sock_S = socket(PF_INET, SOCK_DGRAM, 0);

    /* @IP et num port Serveur */
    bzero((char *) &sa_S, sizeof(struct sockaddr));
    sa_S.sin_family = AF_INET;
    sa_S.sin_addr.s_addr = htonl(INADDR_ANY);
    sa_S.sin_port = htons(UDP_port_S);

    /* Attachement */
    bind(sock_S, (struct sockaddr *) &sa_S,
         sizeof(struct sockaddr));

    /* reception datagramme */
    taille_sa = sizeof(struct sockaddr);


    cout << string("Server Start") << endl;



    recvfrom(sock_S, message, 2048 * sizeof(char), 0,
             (struct sockaddr *) &sa_j1, &taille_sa);

    bool isGui = message[2047] == '1';
    cout << string("isGui : ") ;
    cout << isGui << endl;
    cout << string("Pseudo : ") + string(message) << endl;

    string messageRecv(message);

    Player j1 = Player(message, 'O', isGui);

    sendto(sock_S, "1", 2048 * sizeof(char), 0,
           (struct sockaddr *) &sa_j1, taille_sa);


    recvfrom(sock_S, message, 2048 * sizeof(char), 0,
             (struct sockaddr *) &sa_j2, &taille_sa);
    cout << string("Pseudo : ") + string(message) << endl;

    isGui = message[2047] == '1';
    cout << string("isGui : ") ;
    cout << isGui << endl;
    Player j2 = Player(message, 'X', isGui);


    sendto(sock_S, "2", 2048 * sizeof(char), 0,
           (struct sockaddr *) &sa_j2, taille_sa);


    Board b = Board();

    while (1) {
        playerTurn(&b, &j1, &j2, sock_S, sa_j1, sa_j2, taille_sa,&nbPlayerWantTofinish);
        playerTurn(&b, &j2, &j1, sock_S, sa_j2, sa_j1, taille_sa,&nbPlayerWantTofinish);

    }
    /* fin */
    close(sock_S);
    perror("close ");

    exit(EXIT_SUCCESS);

}


std::string prepareMessage(std::string board, Player *j1, Player *j2) {
    std::string msg = j1->getPseudo() + " Symbol : 0 Nb Pawn captured : " + std::to_string(j1->getPawnCaptured()) + "\n";
    msg += j2->getPseudo() + " Symbol : X Nb Pawn captured : " + std::to_string(j2->getPawnCaptured()) + "\n";
    msg += "# : empty.\n";
    msg += "\n";
    msg += board + "\n";
    msg += "\n";
    msg += "To play, enter de x y coord of the case or you can pass your turn by writing 'pass' (if the two play pass their turn, it will be the end of the game). Don't forget to follow this pattern (x,y).\n";
    msg += "x : N° of the LINE (start from 0)\n";
    msg += "y : N° of the column (start from 0)\n";
    return msg;
}

void sendBoardTo(Board *b, Player *pWhoPlay, Player *otherPlayer, int sock_S, sockaddr_in sa_client, bool isGuiClient,
                 unsigned int taille_sa) {
    string msg;
    char msg2[2048];
    if (!isGuiClient) {
        if (pWhoPlay->getSymbol() == '0') {
            msg = prepareMessage(b->getString(), pWhoPlay, otherPlayer);
        } else {
            msg = prepareMessage(b->getString(), otherPlayer, pWhoPlay);
        }
        stringToCharTab(msg,msg2);
    } else {
        b->getStringForGui(msg2);
        string j1;
        string j2;
        if (pWhoPlay->getSymbol() == '0') {
             j1 = string(to_string(pWhoPlay->getPawnCaptured()));
             j2 = string(to_string(otherPlayer->getPawnCaptured()));
        } else {
            j1 = string(to_string(otherPlayer->getPawnCaptured()));
            j2 = string(to_string(pWhoPlay->getPawnCaptured()));
        }
        cout << string("J1 : ") + j1 << endl;
        cout << string("J2 : ") + j2 << endl;
        if(j1.size() == 3){
            msg2[2042] = j1[0];
            msg2[2043] = j1[1];
            msg2[2044] = j1[2];
        }
        else if (j1.size() == 2){
            msg2[2042] = '0';
            msg2[2043] = j1[0];
            msg2[2044] = j1[1];
        }
        else {
            msg2[2042] = '0';
            msg2[2043] = '0';
            msg2[2044] = j1[0];
        }

        if(j2.size() == 3){
            msg2[2045] = j2[0];
            msg2[2046] = j2[1];
            msg2[2047] = j2[2];
        }
        else if (j2.size() == 2){
            msg2[2045] = '0';
            msg2[2046] = j2[0];
            msg2[2047] = j2[1];
        }
        else {
            msg2[2045] = '0';
            msg2[2046] = '0';
            msg2[2047] = j2[0];
        }

    }
    sendto(sock_S, msg2, 2048 * sizeof(char), 0, (struct sockaddr *) &sa_client, taille_sa);
}

void playerTurn(Board *b, Player *pWhoPlay, Player *otherPlayer, int sock_S, sockaddr_in sa_pWhoPlay,
                sockaddr_in sa_otherPlayer, unsigned int taille_sa, int *nbPlayerWantTofinish) {
    char message[2048];
    std::string msg;
    cout << string("Nb pass : ") + to_string(*nbPlayerWantTofinish) << endl;
    if((*nbPlayerWantTofinish) == 2){
        sendto(sock_S, "stop", 2048 * sizeof(char), 0, (struct sockaddr *) &sa_pWhoPlay, taille_sa);
        sendto(sock_S, "stop", 2048 * sizeof(char), 0, (struct sockaddr *) &sa_otherPlayer, taille_sa);
        close(sock_S);
        perror("close ");

        exit(EXIT_SUCCESS);
    }
    else{
    sendBoardTo(b,pWhoPlay,otherPlayer,sock_S,sa_otherPlayer,otherPlayer->getIsGuiClient(),taille_sa);
    sendBoardTo(b,pWhoPlay,otherPlayer,sock_S,sa_pWhoPlay,pWhoPlay->getIsGuiClient(),taille_sa);


    while (1) {
        if(!pWhoPlay->getIsGuiClient()){
        sendto(sock_S, "It's your turn ! Please enter the x,y of the case where you want to play :",
               2048 * sizeof(char), 0,
               (struct sockaddr *) &sa_pWhoPlay, taille_sa);
        }

        cout << "player " + pWhoPlay->getPseudo() + " mind" << endl;

        recvfrom(sock_S, message, 2048 * sizeof(char), 0,
                 (struct sockaddr *) &sa_pWhoPlay, &taille_sa);


        cout << "player " + pWhoPlay->getPseudo() + " do that" + string(message) << endl;

        string msgIf(message);
        if(msgIf.substr(0,4) == "pass"){
            *nbPlayerWantTofinish += 1;
            sendto(sock_S, "ok", 2048 * sizeof(char), 0,
                   (struct sockaddr *) &sa_pWhoPlay, taille_sa);
            break;
        }
        else if (message[3] == '\000' && message[1] == ',' && (int) message[0] >= 48 && (int) message[0] <= 57 &&
            (int) message[2] >= 48 && (int) message[2] <= 57) {
            try {
                int x, y;
                x = message[0] - '0';
                y = message[2] - '0';
                b->setPawn(new Pawn(x, y, pWhoPlay));
                sendto(sock_S, "ok", 2048 * sizeof(char), 0,
                       (struct sockaddr *) &sa_pWhoPlay, taille_sa);
                cout << string("all right") << endl;
                *nbPlayerWantTofinish = 0;
                break;
            }
            catch (runtime_error err) {
                sendto(sock_S, "invalid move", 2048 * sizeof(char), 0,
                       (struct sockaddr *) &sa_pWhoPlay, taille_sa);
                cout << string("invalid input : Impossible move") << endl;

                sendBoardTo(b,pWhoPlay,otherPlayer,sock_S,sa_pWhoPlay,pWhoPlay->getIsGuiClient(),taille_sa);


            }
        } else {
            sendto(sock_S, "invalid input", 2048 * sizeof(char), 0,
                   (struct sockaddr *) &sa_pWhoPlay, taille_sa);
            cout << string("invalid input : out of range or invalid string") << endl;

            sendBoardTo(b,pWhoPlay,otherPlayer,sock_S,sa_pWhoPlay,pWhoPlay->getIsGuiClient(),taille_sa);

        }

    }}

}

void stringToCharTab(string str,char res[2048]){
    for (int i = 0; i < str.size(); ++i) {
        if(str[i] == '\000'){
            res[i] = '\000';
            break;
        }
        else{
            res[i] = str[i];
        }
    }

}


