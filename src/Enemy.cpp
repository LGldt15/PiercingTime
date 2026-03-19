#include "Enemy.h"


Enemy::~Enemy(int health,int damage,bool a,float s){
    hp=health; attack=damage; isAlive=a; speed=s;
}

void Enemy::move(const Position& player){
    Position dir = player - position; //direction
    float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y); //norme du vecteur 
    if (dist > 0) position += dir / dist * speed; //normalisation puis * vitesse
}
