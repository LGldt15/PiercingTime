#ifndef PLAYER_H
#define PLAYER_H

#include "Position.h"
#include "Stats.h"
#include "Controls.h"
#include "Enemy.h"
#include "Inventory.h"

class Player {
private:
    Stats stats;
   
    Inventory inventory;
    unsigned int experience;
    unsigned int gold;
    unsigned int sprites;
    
    unsigned int width;
    unsigned int height;


public:
    Player();
    ~Player();
    bool dead;
    Position position;
    unsigned int cooldown;
    Stats& getStats();
    Position getPosition();
    unsigned int getHeight();
    unsigned int getWidth();
    unsigned int getSprites();
    unsigned int getExperience();
    unsigned int getGold();
    void setGold(unsigned int g);

    Inventory& getInventory();
    unsigned int getAttackWithBonus() const;

    void move(const Controls &c, unsigned int winWidth, unsigned int winHeight);
    bool takeDamage(const Enemy &enemy);
    bool takeDamageBullet(class Bullet &bullets);
    void shoot(class Bullet &bullets, unsigned int nbE, Enemy* tabE) const;
};

#endif