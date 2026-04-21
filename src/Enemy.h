#ifndef _ENEMY_H
#define _ENEMY_H

//nos include
#include "Bullet.h"
#include "Inventory.h"

class Enemy{
private:
    unsigned int height,width;
    Stats stats;
    unsigned int experience;
public:
    unsigned int sprite;
    Position position;
    bool isAlive;
    Enemy* next;

    Enemy(int health=1,int damage=1,bool a=false,float s=0.05,int idS=0);
    ~Enemy();
    
    void shoot(Bullet &bullets);
    bool takeDamageBullet(Bullet &bullets);
    void move(Position &player);
    void moveAgro(Position &player);
    void moveShooter(Position &player);

    unsigned int getSprite();
    Position getPosition();
    
    Stats& getStats();
    const Stats& getStats()const;

};











#endif