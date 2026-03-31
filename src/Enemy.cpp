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
    if(position.posX<0){position.posX=0.f;}else if(position.posX>800){position.posX=800.f;} //prévient la sortie de case
    if(position.posY<0){position.posY=0.f;}else if(position.posY>800){position.posY=800.f;} 
    if(stats.bulletSpeed!=0){moveShooter(player);return;}
    moveAgro(player);
}

void Enemy::moveAgro(Position &player){
    Position dir = player - position; //direction
    float dist = dir.length(); //norme du vecteur 
    if (dist > 0) position =position+ dir / dist * stats.playerSpeed; //normalisation puis * vitesse
}

void Enemy::moveShooter(Position &player){
    float maxDist=200; // taille de l'écart entre joueur et l'ennemy
    Position dir = player - position; //direction vers le joueur
    bool q =(reinterpret_cast<std::uintptr_t>(this) >> 4) & 1;//vaut 1 ou 0, pour le sens de l'ennemy, constant et identifié par son adresse
    float x=-1*(q*2-1)*dir.posY; // on ajoute +ou- 90 deg au vecteur direction
    dir.posY=(q*2-1)*dir.posX;
    dir.posX=x;
    //remarque: on ne change pas la norme du vecteur donc on peut encore savoir si on est trop proche 
    if(dir.length()<=maxDist){//on ajoute un angle pi/4 pour s'éloigner
        x=(dir.posX-(q*2-1)*dir.posY)*0.70710678118;
        dir.posY=(dir.posX+(q*2-1)*dir.posY)*0.70710678118;
        dir.posX=x;
    }
    float dist = dir.length(); //norme du vecteur 
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