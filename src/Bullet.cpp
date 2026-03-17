#include "Bullet.h"

Position::float length(){return sqrt(posX*posX+posY*posY;)}

Position::operator +(Position p){
    posX+p.posX;
    posY+p.posY;
    return this;
}

Position::operator -(Position p){
    posX-p.posX;
    posY-p.posY;
    return this;
}

Position::operator +(Position p){
    posX+p.posX;
    posY+p.posY;
    return this;
}

Position::operator *(float q){
    posX*q;
    posY*q;
    return this;
}

Position::operator /(float q){
    ASSERT(q!=0)
    posX/q;
    posY/q; 
    return this;
}