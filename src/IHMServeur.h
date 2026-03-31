#ifndef _IHMSERVEUR_H
#define _IHMSERVEUR_H

#include <list>
#include "Game.h"
#include <SFML/Network.hpp>
class IHMServeur{
private:
    Game game;

    int port;
    sf::TcpListener listener;
    sf::SocketSelector selector;
    std::list<sf::TcpSocket*> clients;


public:
    IHMServeur(int p);
    void gameLoop();
    void run();
};

#endif