#ifndef _MAP_H
#define _MAP_H

#include "Bullet.h"
#include "Enemy.h"
#include "Inventory.h"
#include "Player.h"


class Map{
private:
    int idMap;
    Enemy enemies[50];
    int nbEnemies;
    Bullet bullets[500];
    int nbBullets;

    //gestion de waves
    int waveID;
    float timer;
    bool dead;

public:
    Map();
    Map(int idS,Player &p,int nbP);

    void move( unsigned int winWidth,unsigned int winHeight,Player* players,int nbPlayers);//local
    void move(Player* players,int nbPlayers);//serveur
    void damageE();
    void damageP(Player* players,int nbPlayers , int player);
    void damageAll(Player* players,int nbPlayers);

    void update(  unsigned int winWidth, unsigned int winHeight,Player* players,int nbPlayers);
    void update(Player* players,int nbPlayers);
    //utilities to get stuff vacj up to the renderer
    int getMapId();

    int getNbEnemies();
    Enemy* getEnemies();


    int getNbBullet();
    Bullet* getBullets();


    void startWave();
    bool isDead();
    bool isTimeUp() { return (timer >= 150.0f); }
    void resetTimer() { timer = 0.0f; } 

    void restart();

};



#endif