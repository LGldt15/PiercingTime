#ifndef _PLAYER_H
#define _PLAYER_H

#include <vector>


//nos include
#include "Bullet.h"
#include "Enemy.h"

struct Controls{
    bool up;
    bool down;
    bool right;
    bool left;
    bool pause;
    bool select;
};

class Player{
private:
    unsigned int sprites;
    unsigned int height,width;
    std::vector<float> position;
    unsigned int hp;
    unsigned int attack;
    unsigned int experience;
    float speed;
public:
    Player();
    ~Player();
    bool dead;
    void shoot(Bullet *bullets);
    bool takeDamageBullet(Bullet &bullets);
    bool takeDamage(const Enemy &enemies);
    void move(const Controls &c);
    void levcelUP();
    std::vector<float> getPos();
};










#endif
