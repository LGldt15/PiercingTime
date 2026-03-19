#include "Bullet.h"
#include "cmath"

float  Position::length(){
    return sqrt(posX*posX+posY*posY);
}

Position Position::operator +(Position p2){
    posX+=p2.posX;
    posY+=p2.posY;
    return *this;
}

Position Position::operator -(Position p2){
    posX-=p2.posX;
    posY-=p2.posY;
    return *this;
}

Position Position::operator *(float q){
    posX*=q;
    posY*=q;
    return *this;
}

Position Position::operator /(float q){
    if(q!=0){
        posX/=q;
        posY/=q; 
    }
    return *this;
}