#include "Bullet.h"
#include "cmath"

float  Position::length(){
    return sqrt(posX*posX+posY*posY);
}

void Position::operator +(Position p2){
    posX+=p2.posX;
    posY+=p2.posY;
}

void Position::operator -(Position p2){
    posX-=p2.posX;
    posY-=p2.posY;
}

//Position Position::operator +(Position p2){
//    posX+=p2.posX;
//    posY+=p2.posY;
//}

void Position::operator *(float q){
    posX*=q;
    posY*=q;
}

void Position::operator /(float q){
    if(q!=0){
        posX/=q;
        posY/=q; 
    }
}