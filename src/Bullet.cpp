#include "Bullet.h"
#include "cmath"

Bullet::Bullet(){
    next=nullptr;
    pos.posX=pos.posY=50;
    speed.posX=speed.posY=0;
    damage=0;
    fromPlayer=true;
    sprite=0;
    
}

Bullet::Bullet(Bullet *n,Position p,Position S,unsigned int d,bool fP){
    next=n;
    sprite=0;
    pos=p;
    speed=S;
    damage=d;
    fromPlayer=fP;
    
}

Bullet::Bullet(Position p,Position S,unsigned int d,bool fP){
    next=nullptr;
    sprite=0;
    pos=p;
    speed=S;
    damage=d;
    fromPlayer=fP;
    
}

Bullet::~Bullet(){}   


unsigned int Bullet::hitOrMiss(Position & posE,unsigned int heightE, unsigned int widthE){//renvoie les degat fait un une entite en foncione de la sa position, de sa hauteur et de sa largeur
    height=width=10;
    bool hit=(pos.posX < posE.posX + widthE && pos.posX + width > posE.posX &&
        pos.posY < posE.posY + heightE && pos.posY + height > posE.posY);
    if(hit){
        unsigned int temp=damage; // on récupère les dégats
        damage=0; // on met damage à 0 pour détruire facilement l'objet
        return temp;
    }
    return 0;
}


void Bullet::move(){
    pos=pos+speed;
}


int Bullet::getSprite(){
    return sprite;
}