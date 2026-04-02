#ifndef _BULLET_H
#define _BULLET_H
#include "Position.h"

class Bullet{
private: 
    unsigned int sprite;
    unsigned int height,width;
public:
    Position speed;
    Position pos;
    bool fromPlayer;//true: viens d'un joueur , false: viens d'un ennemy
    unsigned int damage;
    Bullet* next;
    Bullet();
    Bullet(Bullet *n, Position p={0,0}, Position S={0,0}, unsigned int d=0, bool fP=true);
    Bullet(Position p,Position S,unsigned int d,bool fP);
    ~Bullet();
    unsigned int hitOrMiss(Position & posE,unsigned int heightE, unsigned int widthE);//renvoie les degat fait un une entite en foncione de la sa position
    void move();
    int getSprite();
};









#endif