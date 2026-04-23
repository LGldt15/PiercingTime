#ifndef _PLAYER_H
#define _PLAYER_H

//nos include
#include "Bullet.h"
#include "Enemy.h"
#include "Inventory.h"
#include "Controls.h"


/*
 *@class Player
 *@brief gère le(s) joueur(s) humain(s)
*/
class Player{
private:
    Stats stats;
    Inventory inventory;
public:
    Position position;// !!! à utiliser avec le get
    unsigned int height,width;// !!! à utiliser avec le get
    unsigned int sprites;// !!! à utiliser avec le get
    unsigned int experience;// !!! à utiliser avec le get
    unsigned int gold;// !!! à utiliser avec le get et set
    int cooldown;
    bool dead;
    bool start;


    Player();
    ~Player();

    void shoot(Bullet &bullets, unsigned int nbE, Enemy* tabE)const;
    bool takeDamageBullet(Bullet &bullets);
    bool takeDamage(const Enemy &enemy);
    void move(const Controls &c,unsigned int winWidth,unsigned int winHeight);
    void levcelUP();

    Stats& getStats();
    Position getPosition();


    unsigned int getHeight();
    unsigned int getWidth();
    unsigned int getSprites();
    unsigned int getExperience();
    unsigned int getGold();
    Inventory& getInventory();
    void setGold(unsigned int g);


    //server managment
    int getIdMulti();
    void doWeStart(Controls c);
};










#endif
