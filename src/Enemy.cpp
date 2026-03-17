#include "Enemy.h"

Enemy::Enemy(bool a){
    hp=1;
    attack=0;
    speed=0.05;
    position.x=rand()%800;
    position.y=rand()%800;
    isAlive=a;
}

Enemy::~Enemy(){}

void Enemy::move(const Position& player){
    Position dir;//direction
    dir.posX = player.posX - position.posX; dir.posY = player.posY - position.posY; 
    float dist = std::sqrt(dir.posX * dir.posY + dir.posY * dir.posY); //norme du vecteur 
    if (dist > 0) position += dir / dist * speed; //normalisation puis * vitesse
}
