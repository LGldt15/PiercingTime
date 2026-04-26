#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>


Enemy::Enemy(int health,int damage,bool a,float s,int idS, std::string t){
    stats.hp=health; stats.attackDamage=damage; stats.playerSpeed=s; stats.bulletSpeed=0;
    isAlive=a;
    position.posX=rand()%800;
    position.posY=rand()%800;
    sprite=idS;
    height=width=100;
    next=nullptr;
    std::strcpy(type, t.c_str());
    rotationSide=rand()%1;
    
}

Enemy::~Enemy(){

}
Stats& Enemy::getStats(){return stats;}
const Stats& Enemy::getStats()const{return stats;}

void Enemy::move(Position& player){
    std::string t;
    t= type;
    bool shooter= ( t=="Archer")||(t=="Spearman");//...
    bool deserter= (t=="Rabbit");//...
    if(int(position.posX)<50){ //prévient la sortie de case
        position.posX=50.f;
        return;
    }else if(int(position.posX)>750){
        position.posX=750.f;
        return;
    }
    if(int(position.posY)<50){
        position.posY=50.f;
        return;
    }else if(int(position.posY)>750){
        position.posY=750.f;
        return;
    } 
    if(shooter){moveShooter(player);return;}
    if(deserter){moveDeserter(player);return;}
    moveAgro(player);
}

void Enemy::moveAgro(Position &player){ // fonce sur le joueur
    Position dir = player - position; //direction
    float dist = dir.length(); //norme du vecteur 
    if (dist > 0) position =position+ dir / dist * stats.playerSpeed; //normalisation puis * vitesse
}

void Enemy::moveShooter(Position &player){ // move de manière circulaire et reste à distance du joueur
    float maxDist=200; // taille de l'écart entre joueur et l'ennemy
    Position dir = player - position; //direction vers le joueur
    float dist = dir.length(); //norme du vecteur 
    if (dist<=1e-1) return;
    // on ajoute +ou- pi/2 rad au vecteur direction, ou 3pi/4 si trop proche 
    if(dist<=maxDist){
        dir.rotate(-0.70710678118,(rotationSide*2-1)*0.70710678118); // cos(3pi/4)=-sin(3pi/4)=-0.70710678118  
    }else{dir.rotate(0,(rotationSide*2-1));}
  
    position = position + (dir / dist) * stats.playerSpeed; //normalisation puis * vitesse
}

void Enemy::moveDeserter(Position &player){//move qui fuit le joueur et ne se coinse pas 
    //idée: on trace pleins de rayons à partir de l'enemy, il va vers celui qui le fait le plus bouger en restant loing du joueur 

    Position dir = player - position;//direction vers le joueur
    float dist = dir.length();
    if(dist < 1e-5f) return;
    dir = dir / dist; //normalisation

    const int n = 24;
    float bestScore = -1e9; // score du meilleur rayon initialisé très bas
    Position bestDir = -dir; // fallback = fuite directe
    for(int i = 1; i < n; i++){
        float angle = i * (2*3.14/n); // 360° divisées en (n-1) rayons
        
        float c = cos(angle);
        float s = sin(angle);
        
        Position ray = dir;
        ray = ray.rotate(c, s); // rayon testé 
        ray= ray / ray.length();// normalisation
        
        Position hit = ray.squareIntersection(position, 0,0,800,800); // ray tracing
        float d = (hit - position).length();// distance à l'intersection

        // pénalité si direction vers le joueur
        float penalty = (ray * dir); // >0 = vers joueur
        float score = d*(1.2f - penalty);

        if(score > bestScore){
            bestScore = score;
            bestDir = ray;
        }
    }
    position = position + bestDir * (stats.playerSpeed*2);
}


 void Enemy::shoot(Bullet &bullets, unsigned int nbP, Player* tabP)const{
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
    if(distMin>=400) return; // il faut étre proche du joueur pour lui tirer dessus
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
    dmg=bullets.hitOrMiss(position,{position.posX+50,position.posY+100});
    if(dmg==0)return false;
    if (stats.hp<=dmg){stats.hp=0;isAlive=false;} 
    else stats.hp-=dmg;
    return true;
}

int Enemy::getGold(){
    return gold;
}
