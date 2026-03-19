#include "Enemy.h"
#include <cmath>

Enemy::Enemy(int health,int damage,bool a,float s){
    hp=health; attack=damage; isAlive=a; speed=s;
}

void Enemy::move(Position& player){
    Position dir = player - position; //direction
    float dist = sqrt(dir.posX * dir.posX + dir.posY * dir.posY); //norme du vecteur 
    if (dist > 0) position =position+ dir / dist * speed; //normalisation puis * vitesse
}
