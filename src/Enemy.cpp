#include "Enemy.h"
#include <cmath>

Enemy::Enemy(int health,int damage,bool a,float s,int idS){
    hp=health; attack=damage; isAlive=a; speed=s; sprite=idS ;
    position.posX=rand()%800;
    position.posY=rand()%800;
    next=nullptr;
}

Enemy::~Enemy(){

}

void Enemy::move(Position& player){
    Position dir = player - position; //direction
    float dist = sqrt(dir.posX * dir.posX + dir.posY * dir.posY); //norme du vecteur 
    if (dist > 0) position =position+ dir / dist * speed; //normalisation puis * vitesse
}

bool Enemy::takeDamageBullet(Bullet &bullets){
    if(!bullets.fromPlayer)return false;
    unsigned int dmg;
    Position hitbox;
    hitbox.posX=height;
    hitbox.posY=width;
    dmg=bullets.hitOrMiss(position,hitbox);
    if(dmg==0)return false;
    if (hp<=dmg){hp=0;isAlive=false;} 
    else hp-=dmg;
    return true;
 }