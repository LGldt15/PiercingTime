#ifndef _BULLET_H
#define _BULLET_H

class Bullet{
private:
    Position pos;
    Position speed; // composantes en x et y du vecteur vitesse
    unsigned int sprite;
public:
    bool fromPlayer;//true: viens d'un joueur , false: viens d'un ennemy
    unsigned int damage;
    Bullet* next;
    Bullet();
    Bullet(Bullet &n, float x=0, float y=0, float sX=0, float sY=0, unsigned int d=0, bool fP=true);
    ~Bullet();
    unsigned int hitOrMiss(Position min,Position max);//renvoie les degat fait un une entite en foncion de la hitbpx de celle ci(xMin et yMin)
    void move();
    void setPos(Position pos);
    void setSpeed(Position speed);

};









#endif