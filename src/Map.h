#ifndef _MAP_H
#define _MAP_H

#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"

const int MAX_ENEMY = 75;
const int MAX_BULLETS = 500;

class Map{
private:
    int idMap;
    Player* players[4];
    int nbPlayers;

    Enemy enemies[MAX_ENEMY]; 
    int nbEnemies;
    Bullet bullets[MAX_BULLETS];
    int nbBullets;

    //gestion de waves
    int waveID;
    float timer;
    bool dead;

public:
    Map();
    Map(int idS, Player &p, int nbP);
    void move(Player* players,int nbPlayers);
    void move(unsigned int winWidth, unsigned int winHeight,Player* players,int nbPlayers);
    void damageE();
    void damageP(Player* players,int nbPlayers , int player);
    void damageAll(Player* players,int nbPlayers);

    void update(unsigned  int winWidth, unsigned int winHeight,Player* players,int nbPlayers);
    //utilities to get stuff vacj up to the renderer
    int getMapId();

    int getNbEnemies();
    Enemy* getEnemies();


    int getNbBullet();
    Bullet* getBullets();



    //WAVES
    void startWave();
    bool isDead();
    bool isTimeUp() { return (timer >= 150.0f); }
    void resetTimer() { timer = 0.0f; } 

    void restart();
};

#endif