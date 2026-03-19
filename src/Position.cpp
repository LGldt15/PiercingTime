#include "Position.h"
#include <cmath>

float  Position::length(){
    return sqrt(posX*posX+posY*posY);
}

Position Position::operator +(const Position & p2) const {
    Position p;
    p.posX=posX+p2.posX;
    p.posY=posY+p2.posY;
    return p;
}

Position Position::operator -(const Position & p2) const {
    Position p;
    p.posX=posX-p2.posX;
    p.posY=posY-p2.posY;
    return p;
}

Position Position::operator *(const float &q) const {
    Position p;
    p.posX=posX*q;
    p.posY=posY*q;
    return p;
}

Position Position::operator /(const float &q) const {
    if(q!=0){
        Position p;
        p.posX=posX/q;
        p.posY=posY/q;
        return p;
    }
    else{return *this;}

}