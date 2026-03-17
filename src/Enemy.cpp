#include "Enemy.h"
#include "cmath"

Enemy::Enemy(int h,int d,bool a,float s){
    hp=h;
    attack=d;
    speed=s;
    position.posX=rand()%800;
    position.posY=rand()%800;
    isAlive=a;
}

Enemy::~Enemy(){}

void Enemy::move(const Position& player){
    Position dir;//direction
    dir.posX = player.posX - position.posX; dir.posY = player.posY - position.posY; 
    float dist = std::sqrt(dir.posX * dir.posY + dir.posY * dir.posY); //norme du vecteur 
    if (dist > 0) position += dir / dist * speed; //normalisation puis * vitesse
}
