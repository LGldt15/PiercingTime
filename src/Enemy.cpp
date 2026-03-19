#include "Enemy.h"
#include <cmath>



Enemy::~Enemy(){}

void Enemy::move(Position& player){
    Position dir = player - position; //direction
    float dist = std::sqrt(dir.posX * dir.posY + dir.posY * dir.posY); //norme du vecteur 
    if (dist > 0) position =position+ dir / dist * speed; //normalisation puis * vitesse
}
