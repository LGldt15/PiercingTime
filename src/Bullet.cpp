#include "Bullet.h"
#include "cmath"

float  Position::length(){
    return sqrt(posX*posX+posY*posY);
}

Position Position::operator +(Position p2){
    Position p;
    p.posX=posX+p2.posX;
    p.posY=posY+p2.posY;
    return p;
}

Position Position::operator -(Position p2){
    Position p;
    p.posX=posX-p2.posX;
    p.posY=posY-p2.posY;
    return p;
}

Position Position::operator *(float q){
    Position p;
    p.posX=posX*q;
    p.posY=posY*q;
    return p;
}

Position Position::operator /(float q){
    if(q!=0){
        Position p;
        p.posX=posX/q;
        p.posY=posY/q;
        return p;
    }
    else{return *this;}

}


Bullet::Bullet(){
    next=nullptr;
    pos.posX=pos.posY=0;
    speed.posX=speed.posY=0;
    damage=0;
    fromPlayer=true;
}

Bullet::Bullet(Bullet &n,int x,int y,int sX,int sY,int d,bool fp;){
    next=&n;
    sprite=0;
    pos.posX=x;
    pos.posY=y;
    speed.posX=sX;
    speed.posY=sY;
    damage=d;
    fromPlayer=fp;
}

Bullet::~Bullet(){}   


unsigned int Bullet::hitOrMiss(Position min,Position max){//renvoie les degat fait un une entite en foncione de la hitbpx de celle ci(xMin et yMin sont ses coordonner xMax,yMax sont les hauteur et la largeur de la "hitbox")
    if(pos.posX<=max.posX && pos.posX>=min.posX && pos.posY<=max.posY && pos.posY>=min.posY) {
        unsigned int temp=damage; // on récupère les dégats
        damage=0; // on met damage à 0 pour détruire facilement l'objet
        return temp;
    }
    return 0;
}


void Bullet::move(){
    pos=pos+speed;
}