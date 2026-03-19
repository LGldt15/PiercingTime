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
    Position dir = player - position; //direction
    float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y); //norme du vecteur 
    if (dist > 0) position += dir / dist * speed; //normalisation puis * vitesse
}
