#ifndef _IHMSERVEUR_H
#define _IHMSERVEUR_H

#include <list>
#include "Game.h"
#include <SFML/Network.hpp>
#include <thread>
#include <mutex>
/**
 * @class IHMServeur
 *
 * @brief Gestion du protovole de communication entre le serveur(plus precisement une seul partie) et ses client 
 *
 * Une classe pour illustrer l'utilisation de Doxygen pour générer de la documentation.
 */

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
    /**
    * @brief cconstructeur par defaut  
    * 
    * @param i id de la partie
    */

    IHMServeur(int i=0);
    /**
    * @brief game loop gerer par le serveur 
    * 
    */
    void executionLoop();
    /**
    * @brief ajout du 1 er joueur joueur de la room et donc le createur de celle ci 
    * 
    * @param creator socket a laquelle le createur est connecter
    */
    void startWithClient(sf::TcpSocket* creator);
    /**
    * @brief fonction pour gerer la jout d un joueur 
    * 
    * @param player socket a laquelle le nouveau joueur est connecter
    */
    void addPlayer(sf::TcpSocket* player);
    /**
    * @brief fonction pour gererla phase de Shop dans une partie
    * 
    */
    void handleShopInput();
};

#endif