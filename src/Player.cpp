#include "Player.h"

Player::Player(){
    stats.hp=10;
    stats.attackDamage=0;
    //stats.experience;
    //stats.gold;
    stats.playerSpeed=0.1;
    stats.bulletSpeed=0.05;
    position.posX=position.posY=0;
    sprites=0;

}

Player::~Player(){}

Stats& Player::getStats(){return stats;}

void Player::move(const Controls &c){
    float dx=0.0f; // variation de position en largeur
    float dy=0.0f; // variation de position en hauteur
    if(c.up) dy-= stats.playerSpeed;
    if(c.down) dy+= stats.playerSpeed;
    if(c.right) dx+= stats.playerSpeed;
    if(c.left) dx-= stats.playerSpeed;
    if(dx*dy!=0){dx*=0.70710678118; dy*=0.70710678118;} //normalisation à playerSpeed (multiplication par sqrt(2)/2) si cas diagonal
    position.posX+=dx; //ajout à la position courante
    position.posY+=dy;
}

bool Player::takeDamage(const Enemy &enemy){
    float radius = 1; // rayon de la hitbox (à remplacer par le rayon de l'ennemy?)
    unsigned int dmg = 1;// valeur des dégats (à remplacer par la puissance de l'ennemy?)
    Position distance=enemy.position-position;
    if(distance.length()<=radius){
        if (stats.hp<=dmg){stats.hp=0;dead=true;} 
        else stats.hp-=dmg;
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
    if (stats.hp<=dmg){stats.hp=0;dead=true;} 
    else stats.hp-=dmg;
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
    bullets.setSpeed((position-tabE[idMin].position)*stats.bulletSpeed);
    bullets.setPos(position);
    bullets.fromPlayer=true;
 }