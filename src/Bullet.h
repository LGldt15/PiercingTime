#ifndef _BULLET_H
#define _BULLET_H
#include "Position.h"

class Bullet{
private: // composantes en x et y du vecteur vitesse
    unsigned int sprite;
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
    unsigned int hitOrMiss(Position min,Position max);//renvoie les degat fait un une entite en foncion de la hitbpx de celle ci(xMin et yMin)
    void move();
    int getSprite();
};









#endif