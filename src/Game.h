#ifndef _GAME_H
#define _GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
///lib 
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Inventory.h"
#include "Map.h"
#include "Shop.h"


class Game{
private:
    Inventory inventory[4];
    unsigned int nbJoueur;


    Map level;
    unsigned int difficulty;

    //PARTIE shop 
    Player players[4];
    Shop shops[4]; // un shop pour chaque joueur
    bool isShopActive;

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
    void update(Controls c, unsigned int winWidth, unsigned int winHeight);
    //get stuff for rendering
    int getMapId();
    Enemy* getEnemies();
    int getNbEnemys();
    int getPlayerId(int i);
    int getNbBullets();
    Bullet* getBullets();
    //Pour shop
    bool isInShop() const { return isShopActive; }
    void setShopActive(bool active) { isShopActive = active; }

    //recup l idex du shop du joueur
    Shop& getShop(int playerIndex) { return shops[playerIndex]; }
};

#endif