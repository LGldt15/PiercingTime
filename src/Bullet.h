#ifndef _BULLET_H
#define _BULLET_H

struct Position{
    float posX,posY;
    float length();
    void operator +(Position p2);
    void operator -(Position p2);
    void operator *(Position p2);
    void operator *(float f);
    void operator /(float f);

};


class Bullet{
private:

public:

};










#endif