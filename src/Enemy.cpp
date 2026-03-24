#include "Enemy.h"
#include <cmath>

Enemy::Enemy(int health,int damage,bool a,float s,int idS){
    stats.hp=health; stats.attackDamage=damage; isAlive=a; stats.playerSpeed=s; sprite=idS ;
    position.posX=rand()%800;
    position.posY=rand()%800;
    height=width=100;
    next=nullptr;
    stats.bulletSpeed=0;
}

Enemy::~Enemy(){

}
Stats& Enemy::getStats(){return stats;}
const Stats& Enemy::getStats()const{return stats;}

void Enemy::move(Position& player){
    Position dir = player - position; //direction
    float dist = sqrt(dir.posX * dir.posX + dir.posY * dir.posY); //norme du vecteur 
    if (dist > 0) position =position+ dir / dist * stats.playerSpeed; //normalisation puis * vitesse
}

bool Enemy::takeDamageBullet(Bullet &bullets){
    //if(!bullets.fromPlayer)return false;
    unsigned int dmg;
    Position hitbox;
    hitbox.posX=position.posX+height;
    hitbox.posY=position.posY+width;
    dmg=bullets.hitOrMiss(position,hitbox);
    if(dmg==0)return false;
    if (stats.hp<=dmg){stats.hp=0;isAlive=false;} 
    else stats.hp-=dmg;
    return true;
 }