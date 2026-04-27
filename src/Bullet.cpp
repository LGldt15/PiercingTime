#include "Bullet.h"

Bullet::Bullet(){
    //next=nullptr;
    pos.posX=pos.posY=50;
    speed.posX=speed.posY=0;
    damage=0;
    fromPlayer=true;
    sprite=0;
}

//Bullet::Bullet(Bullet *n,Position p,Position S,unsigned int d,bool fP){
//    //next=n;
//    sprite=0;
//    pos=p;
//    speed=S;
//    damage=d;
//    fromPlayer=fP;
//}

Bullet::Bullet(Position p,Position S,unsigned int d,bool fP){
    //next=nullptr;
    sprite=0;
    pos=p;
    speed=S;
    damage=d;
    fromPlayer=fP;
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


int Bullet::getSprite(){
    return sprite;
}