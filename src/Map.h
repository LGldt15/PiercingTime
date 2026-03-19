#ifndef _MAP_H
#define _MAP_H

#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"


class Map{
private:
    int idMap;
    Player* players;
    int nbPlayers;
    Enemy enemies[50];
    int nbEnemies;
    Bullet bullets[500];
    int nbBullets;
public:
    Map();
    Map(int idS,Player &p,int nbP);

    void move(Controls &c);
    void damageE();
    void damageP();
    void damageAll();

    void update(Controls &c);


};

#endif