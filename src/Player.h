#ifndef _PLAYER_H
#define _PLAYER_H

<<<<<<< HEAD
//eventuellement initialiser les stats 
=======

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
>>>>>>> 49d8d7c4d7c0de7889ead7bac7e3d482bfd7522e

class Player{
private:
    unsigned int sprites;
    unsigned int height,width;
    unsigned int hp;
    unsigned int attack;
    unsigned int experience;
    float speed;
public:
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
