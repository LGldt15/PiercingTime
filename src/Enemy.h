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
    unsigned int speed;
public:
    Position position;
    bool isAlive;
    Enemy* next;
    Enemy(bool a=false);
    Enemy(int health=1,int damage=0,bool isAlive=false);
    ~Enemy();
    void shoot(Bullet &bullets);
    bool takeDamageBullet(Bullet &bullets);
    void move(const Position &player);
};











#endif