<<<<<<< HEAD
=======
#ifndef _PLAYER_H
#define _PLAYER_H

#include <vector>


class Player{
private:
    unsigned int sprites;
    unsigned int height,width;
    vector<float> position;
    unsigned int hp;
    unsigned int attack;
    unsigned int experience;
    float speed
public:
    Player();
    ~Player();
    void shoot(Bullet *bullets);
    bool takeDamageBullet(Bullet &bullets);
    bool takeDamage(const Enemy &enemies);
    void move();
    void levcelUP();
    bool dead();
    vector<float> getPos();
};










#endif
>>>>>>> 0984e16 (player.h)
