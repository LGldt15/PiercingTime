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
    int posX,posY;
    int speedX,speedY;
    bool hit;///si sa attaque les enemie u les joueur
    //sf::Sprite* sprite;
public:
    int damage;
    Bullet* next;
    Bullet();
    //Bullet(sf::Texture &t,Bullet &n, int x=0,int y=0,int sX=0,int sY=0,int d=0);
    ~Bullet();
    int hitOrMiss(int xMin,int xMax,int yMin,int yMax);//renvoie les degat fait un une entite en foncione de la hitbpx de celle ci(xMin et yMin sont ses coordonner xMax,yMax sont les hauteur et la largeur de la "hitbox")
    void move();
    //void render(sf::RenderWindow &window);
};









#endif