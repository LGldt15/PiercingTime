#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include <cmath>
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
    type=t;
    rotationSide=rand()%1;
    
}

Enemy::~Enemy(){

}
Stats& Enemy::getStats(){return stats;}
const Stats& Enemy::getStats()const{return stats;}

void Enemy::move(Position& player){
    bool shooter= (type=="Archer")||(type=="Spearman");//...
    bool deserter= (type=="Rabbit");//...
    if(position.posX<50){position.posX=50.f;}else if(position.posX>750){position.posX=750.f;} //prévient la sortie de case
    if(position.posY<50){position.posY=50.f;}else if(position.posY>750){position.posY=750.f;} 
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
    //bool q =(reinterpret_cast<std::uintptr_t>(this) >> 4) & 1;//vaut 1 ou 0, pour le sens de l'ennemy, constant et identifié par son adresse
    float x=-1*(rotationSide*2-1)*dir.posY; // on ajoute +ou- 90 deg au vecteur direction
    dir.posY=(rotationSide*2-1)*dir.posX;
    dir.posX=x;
    //remarque: on ne change pas la norme du vecteur donc on peut encore savoir si on est trop proche 
    if(dir.length()<=maxDist){//on ajoute un angle pi/4 pour s'éloigner
        x=(dir.posX-(rotationSide*2-1)*dir.posY)*0.70710678118;
        dir.posY=(dir.posX+(rotationSide*2-1)*dir.posY)*0.70710678118;
        dir.posX=x;
    }
    float dist = dir.length(); //norme du vecteur 
    if (dist > 0) position =position+ (dir / dist) * stats.playerSpeed; //normalisation puis * vitesse
}

void Enemy::moveDeserter(Position &player){//move qui fuit le joueur et ne se coinse pas 
    //idée: on trace pleins de rayons à partir de l'enemy, il va vers celui qui le fait le plus bouger en restant loing du joueur 

    Position dir = player - position;//direction vers le joueur
    float dist = dir.length();
    if(dist < 1e-5f) return;
    dir = dir / dist; //normalisation

    const int n = 24;
    float bestScore = -1e9; // score du meilleur rayon
    Position bestDir = -dir; // fallback = fuite directe

    for(int i = 0; i < n; i++){
        float angle = i * (2*M_PI/n); // 330° divisées en n rayons
        
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
    dmg=bullets.hitOrMiss(position,{position.posX+50,position.posY+100});
    if(dmg==0)return false;
    if (stats.hp<=dmg){stats.hp=0;isAlive=false;} 
    else stats.hp-=dmg;
    return true;
 }