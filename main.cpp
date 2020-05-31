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

#define UDP_port_S 8000

using namespace std;

std::string prepareMessage(std::string board, Player *j1, Player *j2);

void playerTurn(Board *b, Player *pWhoPlay, Player *otherPlayer, int sock_S, sockaddr_in sa_j1, sockaddr_in sa_j2,
                unsigned int taille_sa);

void convertStringtoCharTab(string str, char tab[2048]);

int main() {
    int sock_S;

    char message[2048];

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

    recvfrom(sock_S, message, 2048 * sizeof(char), 0,
             (struct sockaddr *) &sa_j1, &taille_sa);
    string msg2(message);
    cout << msg2 << endl;

    Player j1 = Player(message, "O");

    sendto(sock_S, "1", 2048 * sizeof(char), 0,
           (struct sockaddr *) &sa_j1, taille_sa);


    recvfrom(sock_S, message, 2048 * sizeof(char), 0,
             (struct sockaddr *) &sa_j2, &taille_sa);


    msg2 = string(message);
    cout << msg2 << endl;


    Player j2 = Player(message, "X");

    sendto(sock_S, "2", 2048 * sizeof(char), 0,
           (struct sockaddr *) &sa_j2, taille_sa);


    Board b = Board();

    while (1) {
        playerTurn(&b, &j1, &j2, sock_S, sa_j1, sa_j2, taille_sa);
        playerTurn(&b, &j2, &j1, sock_S, sa_j2, sa_j1, taille_sa);

    }
    /* fin */
    close(sock_S);
    perror("close ");

    exit(EXIT_SUCCESS);

}


std::string prepareMessage(std::string board, Player *j1, Player *j2) {
    std::string msg = "J1 : " + j1->getPseudo() + " have the symbol : O\n";
    msg += "J2 : " + j2->getPseudo() + " have the symbol : X\n";
    msg += "# means empty.\n";
    msg += board + "\n";
    msg += "To play, enter de x y coord of the case. Don't forget to follow this pattern (x,y).\n";
    msg += "x : N° of the LINE (start from 0)\n";
    msg += "y : N° of the column (start from 0)\n";
    return msg;
}

void playerTurn(Board *b, Player *pWhoPlay, Player *otherPlayer, int sock_S, sockaddr_in sa_pWhoPlay,
                sockaddr_in sa_otherPlayer, unsigned int taille_sa) {
    char message[2048];
    std::string msg;

    if (pWhoPlay->getSymbol() == "0") {
        msg = prepareMessage(b->getString(), pWhoPlay, otherPlayer);
    } else {
        msg = prepareMessage(b->getString(), otherPlayer, pWhoPlay);
    }

    sendto(sock_S, msg.c_str(), 2018 * sizeof(char), 0,
           (struct sockaddr *) &sa_otherPlayer, taille_sa);


    sendto(sock_S, msg.c_str(), 2048 * sizeof(char), 0,
           (struct sockaddr *) &sa_pWhoPlay, taille_sa);


    while (1) {


        sendto(sock_S, msg.c_str(), 2048 * sizeof(char), 0,
               (struct sockaddr *) &sa_pWhoPlay, taille_sa);


        sendto(sock_S, "It's your turn", 2048 * sizeof(char), 0,
               (struct sockaddr *) &sa_pWhoPlay, taille_sa);


        cout << "player " + pWhoPlay->getPseudo() + " mind" << endl;

        recvfrom(sock_S, message, 2048 * sizeof(char), 0,
                 (struct sockaddr *) &sa_pWhoPlay, &taille_sa);


        cout << "player " + pWhoPlay->getPseudo() + " do that" + string(message) << endl;

        if (message[3] == '\000' && message[1] == ',' && (int) message[0] >= 48 && (int) message[0] <= 57 &&
            (int) message[2] >= 48 && (int) message[2] <= 57) {
            try {
                int x, y;
                x = message[0] - '0';
                y = message[2] - '0';
                b->setPawn(new Pawn(x, y, pWhoPlay));
                sendto(sock_S, "ok", 2048 * sizeof(char), 0,
                       (struct sockaddr *) &sa_pWhoPlay, taille_sa);
                cout << string("all right") << endl;
                break;
            }
            catch (runtime_error err) {
                sendto(sock_S, "invalid move", 2048 * sizeof(char), 0,
                       (struct sockaddr *) &sa_pWhoPlay, taille_sa);
                cout << string("invalid input : Impossible move") << endl;

            }
        } else {
            sendto(sock_S, "invalid input", 2048 * sizeof(char), 0,
                   (struct sockaddr *) &sa_pWhoPlay, taille_sa);
            cout << string("invalid input : out of range or invalid string") << endl;
        }

    }

}

void convertStringtoCharTab(string str, char tab[2048]) {
    for (int i = 0; i < str.size(); ++i) {
        tab[i] = str.at(i);
    }
    tab[str.size()] = '\0';
};