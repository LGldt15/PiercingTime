#ifndef _MAP_H
#define _MAP_H

#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"


class Map{
private:
    int idMap;
    Player* players[4];
    int nbPlayers;
    Enemy enemies[50];
    int nbEnemies;
    Bullet bullets[500];
    int nbBullets;
public:
    Map();
    Map(int idS,Player &p,int nbP);

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