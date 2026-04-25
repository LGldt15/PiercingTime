#include "Position.h"
#include <cmath>
#include <algorithm>

float  Position::length(){
    return sqrt(posX*posX+posY*posY);
}

float Position::angle(Position & p2){
    return *this*p2/(length()*p2.length());
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

Position Position::operator -() const {
    Position p;
    p.posX=-posX;
    p.posY=-posY;
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

float Position::operator *(const Position & p2) const { // dot product
    return posX*p2.posX + posY*p2.posY;
}

float Position::operator ^(const Position & p2) const { // cross product
    return posX*p2.posY - posY*p2.posX;
}

Position Position::rotate(const float &phi){// rotation de phi rad (à éviter si phi constant)
    float tempX=posX*cos(phi)-posY*sin(phi);
    posY=posX*sin(phi)+posY*cos(phi);
    posX=tempX;
    return *this;
}
Position Position::rotate(const float & c, const float & s){//rotation d'un angle précalculé (à privilégier)
    float tempX=posX*c - posY*s;
    posY=posX*s + posY*c;
    posX=tempX;
    return *this;
}

Position Position::squareIntersection(const Position &origin, unsigned int minX, unsigned int minY, unsigned int maxX, unsigned int maxY){
    float tx1, tx2, ty1, ty2;

    if (fabs(posX) < 1e-6f) {
        tx1 = -INFINITY;
        tx2 = INFINITY;
    } else {
        float invX = 1.0f / posX;
        tx1 = (minX - origin.posX) * invX;
        tx2 = (maxX - origin.posX) * invX;
    }

    if (fabs(posY) < 1e-6f) {
        ty1 = -INFINITY;
        ty2 = INFINITY;
    } else {
        float invY = 1.0f / posY;
        ty1 = (minY - origin.posY) * invY;
        ty2 = (maxY - origin.posY) * invY;
    }

    float tmin = std::max(std::min(tx1, tx2), std::min(ty1, ty2));
    float tmax = std::min(std::max(tx1, tx2), std::max(ty1, ty2));
    float t = (tmin > 0) * tmin + (tmin <= 0) * tmax;
    
    return origin + *this * t; //retourne l'intersection
}
