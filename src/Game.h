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
    Player players[4];
    Inventory inventory[4];
    unsigned int nbJoueur;


    Map level;
    unsigned int difficulty;
    Shop playerShop[4];
    bool isShopActive=false;
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
    void update(Controls *c);
    //get stuff for rendering
    int getMapId();
    Enemy* getEnemies();
    int getNbEnemys();
    int getPlayerId(int i);
    int getNbBullets();
    Bullet* getBullets();

    bool isInShop() const { return isShopActive; }
    void setShopActive(bool active) { isShopActive = active; }

    //recup l idex du shop du joueur
    Shop& getShop(int playerIndex) { return playerShop[playerIndex]; }
    bool isOver(){return level.isDead();};
    bool isTimeUp();     
    bool isPlayerDead();
    void resetTimer();
    void restart(); //reconstruit
};

#endif