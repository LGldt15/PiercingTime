#ifndef _PLAYER_H
#define _PLAYER_H

//eventuellement initialiser les stats 

//nos include
#include "Bullet.h"
#include "Enemy.h"
#include "Inventory.h"



class Player{
private:
    Stats stats;
    unsigned int experience;
public:
    int cooldown;
    unsigned int height,width;
    unsigned int sprites;
    unsigned int gold;
    Position position;
    Player();
    ~Player();
    bool dead;
    void shoot(Bullet &bullets, unsigned int nbE, Enemy* tabE)const;
    bool takeDamageBullet(Bullet &bullets);
    bool takeDamage(const Enemy &enemy);
    void move(const Controls &c);
    void levcelUP();
    //Position getPos();
    Stats& getStats();
};










#endif
