#ifndef _PLAYER_H
#define _PLAYER_H

//eventuellement initialiser les stats 

//nos include
#include "Bullet.h"
#include "Enemy.h"
#include "Inventory.h"



class Player{
private:
    unsigned int sprites;
    unsigned int height,width;
    unsigned int hp;
    unsigned int attack;
    unsigned int experience;
    float speed;
public:
    unsigned int gold; 
    Position position;
    Player();
    ~Player();
    bool dead;
    void shoot(Bullet &bullets);
    bool takeDamageBullet(Bullet &bullets);
    bool takeDamage(const Enemy &enemy);
    void move(const Controls &c);
    void levcelUP();
    Position getPos();
};










#endif
