#ifndef _IHMSERVEUR_H
#define _IHMSERVEUR_H

#include <list>
#include "Game.h"
#include <SFML/Network.hpp>
#include <thread>
#include <mutex>

class IHMServeur{
private:
    Game game;
    Controls inputs[4];
    bool running=true;
    int id;
    sf::SocketSelector selector;
    std::list<sf::TcpSocket*> clients;

    std::thread roomThread;
    std::mutex roomMutex;
public:
    IHMServeur(int i=0);
    void executionLoop();
    void startWithClient(sf::TcpSocket* creator);
    void addPlayer(sf::TcpSocket* player);
};

#endif