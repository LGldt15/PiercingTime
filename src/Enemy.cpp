#include "Enemy.h"
#include "Player.h"
#include <cmath>
#include <string>


Enemy::Enemy(int health,int damage,bool a,float s,int idS,std::string t){
    stats.hp=health; stats.attackDamage=damage; stats.playerSpeed=s; stats.bulletSpeed=0;
    isAlive=a;
    position.posX=rand()%800;
    position.posY=rand()%800;
    sprite=idS;
    height=width=100;
    next=nullptr;
    type=t;
    
}

Enemy::~Enemy(){

}
Stats& Enemy::getStats(){return stats;}
const Stats& Enemy::getStats()const{return stats;}

void Enemy::move(Position& player){
    bool shooter= (type=="Archer")||(type=="Spearman");//...
    if(position.posX<0){position.posX=0.f;}else if(position.posX>800){position.posX=800.f;} //prévient la sortie de case
    if(position.posY<0){position.posY=0.f;}else if(position.posY>800){position.posY=800.f;} 
    if(shooter){moveShooter(player);return;}
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


 void Enemy::shoot(Bullet &bullets, unsigned int nbP, Player* tabP)const{//à update dans player.cpp!!!!!
    //if(nbP==0){bullets.damage=0;return;}
    Position dist=tabP[0].getPosition()-position;
    float distMin=800;
    unsigned int idMin=-1;
    bool canshoot=false;
    for(unsigned int i=0; i<2;i++){
        dist=tabP[i].getPosition()-position;
        if(distMin>=dist.length() && !tabP[i].dead){
            idMin=i;
            distMin=dist.length();
            canshoot=true;
        }
    }
    if(canshoot){
        Position speed=(tabP[idMin].getPosition()-position)/(tabP[idMin].getPosition()-position).length();
        bullets.pos=position;
        bullets.speed=speed*stats.bulletSpeed;
        bullets.damage=stats.attackDamage;
        bullets.fromPlayer=false;
    }
}

bool Enemy::takeDamageBullet(Bullet &bullets){
    if(!bullets.fromPlayer)return false;
    unsigned int dmg;
    dmg=bullets.hitOrMiss(position,height,width);
    if(dmg==0)return false;
    if (stats.hp<=dmg){stats.hp=0;isAlive=false;} 
    else stats.hp-=dmg;
    return true;
 }