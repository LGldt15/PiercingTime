#ifndef _BULLET_H
#define _BULLET_H

struct Position{
    float posX,posY;
    float length();
    Position operator +(Position p2);
    Position operator -(Position p2);
    Position operator *(float f);
    Position operator /(float f);

};


class Bullet{
private:
    Position pos;
    Position speed; // composantes en x et y du vecteur vitesse
    unsigned int sprite;
public:
    bool fromPlayer?;//true: viens d'un joueur , false: viens d'un ennemy
    unsigned int damage;
    Bullet* next;
    Bullet(Bullet &n, int x=0,int y=0,int sX=0,int sY=0,int d=0);
    ~Bullet();
    unsigned int hitOrMiss(int xMin,int xMax,int yMin,int yMax);//renvoie les degat fait un une entite en foncion de la hitbpx de celle ci(xMin et yMin)
    void move();
};









#endif