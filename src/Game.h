#ifndef _GAME_H
#define _GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
///lib 
#include "Enemy.h"
#include "Player.h"
#include "Inventory.h"
#include "Map.h"
#include "Shop.h"


class Game{
private:
    Player players[4];
    Inventory inventory[4];
    unsigned int nbJoueur;


    Map level;
    unsigned int difficulty;
    Shop shop;
public:
    bool inConfig;//pour savoir si on affiche l ajou de joueur ou le jeu
    Game();
    ~Game();
    //utilistaire
    int getNbJoueur();
    Player* getPlayers();
    ///menu stuff (before game starts)
    void setNbPlayers(int i);
    ///in game stuff
    void update(Controls c);
};

#endif