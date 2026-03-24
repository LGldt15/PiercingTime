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
    //unsigned int hp;//stats
    //unsigned int attack;//stats
   // unsigned int experience;//stats
    //float speed;//stats
    //float bulletSpeed;//stats
public:
    int cooldown;
    unsigned int height,width;
    unsigned int sprites;
    //unsigned int gold;//stats
    Position position;
    Player();
    ~Player();
    bool dead;
    void shoot(Bullet &bullets, unsigned int nbE, Enemy* tabE)const;
    bool takeDamageBullet(Bullet &bullets);
    bool takeDamage(const Enemy &enemy);
    void move(const Controls &c,unsigned int winWidth,unsigned int winHeight);
    void levcelUP();
    //Position getPos();
    Stats& getStats();
};










#endif
