#ifndef _ENEMY_H
#define _ENEMY_H

#pragma once
class Player;

//nos include
#include "Bullet.h"
#include "Inventory.h"
#include <string>

class Enemy{
private:
    Stats stats;
    unsigned int experience;
public:
    unsigned int height,width;
    unsigned int sprite;
    Position position;
    bool isAlive;
    Enemy* next;
    std::string type;

    Enemy(int health=1,int damage=1,bool a=false, float s=0.1,int idS=0,std::string t="Caveman");
    ~Enemy();
    
    void move(Position &player);
    void moveAgro(Position &player);
    void moveShooter(Position &player);

    void shoot(Bullet &bullets, unsigned int nbP, Player* tabP)const;
    bool takeDamageBullet(Bullet &bullets);

    unsigned int getSprite();
    Position getPosition();
    
    Stats& getStats();
    const Stats& getStats()const;

};











#endif