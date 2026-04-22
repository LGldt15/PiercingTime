#ifndef _MAP_H
#define _MAP_H

#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"

static const int MAX_ENEMIES = 75;
static const int MAX_BULLETS = 500;

class Map{
private:
    int idMap;
    Player* players[4];
    int nbPlayers;
    

    Enemy enemies[MAX_ENEMIES]; 
    int nbEnemies;
    Bullet bullets[MAX_BULLETS];
    int nbBullets;

public:
    Map();
    Map(int idS, Player &p, int nbP);
    void move(Controls &c, unsigned int winWidth,unsigned int winHeight);
    void damageE();
    void damageP(int player);
    void damageAll();

    void update(Controls &c,  unsigned int winWidth, unsigned int winHeight);
    //utilities to get stuff vacj up to the renderer
    int getMapId();

    int getNbEnemies();
    Enemy* getEnemies();


    int getNbBullet();
    Bullet* getBullets();

};

#endif