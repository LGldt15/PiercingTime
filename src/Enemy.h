#ifndef _ENEMY_H
#define _ENEMY_H

//nos include
#include "Bullet.h"


class Enemy{
private:
    unsigned int sprite;
    unsigned int height,width;
    unsigned int hp;
    unsigned int attack;
    unsigned int experience;
    float speed;
public:
    Enemy();
    Position position;
    bool isAlive;
    Enemy* next;
    Enemy(int health=1,int damage=0,bool a=false,float s=0.05);
    ~Enemy();
    void shoot(Bullet &bullets);
    bool takeDamageBullet(Bullet &bullets);
    void move(Position &player);
};











#endif