#ifndef _BULLET_H
#define _BULLET_H

struct Position{
    float posX,posY;
    float length();
    Position operator +(Position p2);
    Position operator -(Position p2);
    Position operator *(float f);
    Position operator /(float f);

};


class Bullet{
private:

public:

};










#endif