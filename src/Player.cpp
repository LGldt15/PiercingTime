#include "Player.h"
#include "Bullet.h"

Player::Player(){
    hp=10;
    attack=0;
    speed=0.1;
    position.posX=position.posY=0;
    bulletSpeed=0.05;
}

Player::~Player(){}


void Player::move(const Controls &c){
    float dx=0.0f; // variation de position en largeur
    float dy=0.0f; // variation de position en hauteur
    if(c.up) dy-= speed;
    if(c.down) dy+= speed;
    if(c.right) dx+= speed;
    if(c.left) dx-= speed;
    if(dx*dy!=0){dx*=0.70710678118; dy*=0.70710678118;} //normalisation à speed (multiplication par sqrt(2)/2) si cas diagonal
    position.posX+=dx; //ajout à la position courante
    position.posY+=dy;
}

bool Player::takeDamage(const Enemy &enemy){
    float radius = 1; // rayon de la hitbox (à remplacer par le rayon de l'ennemy?)
    unsigned int damage = 1;// valeur des dégats (à remplacer par la puissance de l'ennemy?)
    Position distance=enemy.position-position;
    if(distance.length()<=radius){
        if (hp<=damage){hp=0;dead=true;} 
        else hp-=damage;
        return true;
    }
    return false;
}

bool Player::takeDamageBullet(Bullet &bullets){
    if(bullets.fromPlayer)return false;
    unsigned int dmg;
    Position hitbox;
    hitbox.posX=height;
    hitbox.posY=width;
    dmg=bullets.hitOrMiss(position,hitbox);
    if(dmg==0)return false;
    if (hp<=dmg){hp=0;dead=true;} 
    else hp-=dmg;
    return true;
 }

 void Player::shoot(Bullet &bullets, unsigned int nbE, Enemy* tabE)const{
    if(nbE==0){bullets.damage=0;return;}
    Position dist=tabE[0].position-position;
    float distMin=dist.length();
    unsigned int idMin=0;
    for(unsigned int i=1; i<=nbE;i++){
        dist=tabE[i].position-position;
        if(distMin>dist.length()){
            idMin=i;
            distMin=dist.length();
        }
    }
    bullets.setSpeed((position-tabE[idMin].position)*bulletSpeed);
    bullets.setPos(position);
    bullets.fromPlayer=true;
 }