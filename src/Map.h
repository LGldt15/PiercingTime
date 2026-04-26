#ifndef _MAP_H
#define _MAP_H

#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include <vector>
#include "json.hpp"

const int MAX_ENEMY = 75;
const int MAX_BULLETS = 500;
const int MAX_WAVES = 10;          // Nombre max de vagues
const int MAX_TYPES_PER_WAVE = 3;

//pour le json

struct EnemySpawnData {
    char type[32];
    int count;
    int hp;
    int dmg;
    float speed;
    int spriteId;
};


struct Wave {
    float triggerTime;
    EnemySpawnData enemyTypes[MAX_TYPES_PER_WAVE];
    int nbTypes; 
    bool triggered;
};


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
    int nbWaves;

    Wave waves[MAX_WAVES];

public:
    Map();
    Map(int idS, Player &p, int nbP);
    void move(Player* players,int nbPlayers);
    void move(unsigned int winWidth, unsigned int winHeight,Player* players,int nbPlayers);
    void damageE();
    void damageP(Player* players,int nbPlayers , int player);
    void damageAll(Player* players,int nbPlayers);

    void update(unsigned  int winWidth, unsigned int winHeight,Player* players,int nbPlayers, float time);
    //utilities to get stuff vacj up to the renderer
    int getMapId();

    int getNbEnemies();
    Enemy* getEnemies();


    int getNbBullet();
    Bullet* getBullets();


    float getTimer(){return timer;};
    //WAVES
    void startWave();
    bool isDead();
    bool isTimeUp() { return (timer >= 150.0f); }
    void resetTimer() { timer = 0.0f; } 

    void restart();
    void loadWaves(const char* filename);
    void resetWaves(); 
    bool allWavesFinished(int nbEnemies) const;

};

#endif