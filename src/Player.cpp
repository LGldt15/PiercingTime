#include "Player.h"
#include "Bullet.h"
#include <iostream>

Player::Player() : inventory(0) {
    stats.hp = 10;
    stats.attackDamage = 10;
    stats.playerSpeed = 3;
    stats.bulletSpeed = 10;
    position.posX = position.posY = 0;
    experience = 0;
    gold = 0;
    sprites = 0;
    cooldown = 10;
    width = 30;
    height = 100;
    dead = false;
}

Player::~Player(){}  unsigned int gold;

Stats& Player::getStats(){return stats;}

Position Player::getPosition(){return position;}
unsigned int Player::getHeight(){return height;}
unsigned int Player::getWidth(){return width;}
unsigned int Player::getSprites(){return sprites;}
unsigned int Player::getExperience(){return experience;}
unsigned int Player::getGold(){return gold;}
void Player::setGold(unsigned int g){gold=g;}



void Player::move(const Controls &c,unsigned int winWidth,unsigned int winHeight){
    float dx=0.0f; // variation de position en largeur
    float dy=0.0f; // variation de position en hauteur

    if(c.up) dy-= stats.playerSpeed;
    if(c.down) dy+= stats.playerSpeed;
    if(c.right) dx+= stats.playerSpeed;
    if(c.left) dx-= stats.playerSpeed;
    if(dx*dy!=0){dx*=0.70710678118; dy*=0.70710678118;} //normalisation à playerSpeed (multiplication par sqrt(2)/2) si cas diagonal
   

    position.posX+=dx; //ajout à la position courante
    position.posY+=dy;
    if (position.posX < 0) position.posX = 0;
    if (position.posX +60> winWidth) position.posX = winWidth-60;
    if (position.posY < 0) position.posY = 0;
    if (position.posY +100> winHeight) position.posY = winHeight-101;
     
   

    cooldown--;

}

bool Player::takeDamage(const Enemy &enemy){
    float radius = 1; // rayon de la hitbox (à remplacer par le rayon de l'ennemy?)
    const Stats& statsEnemy=enemy.getStats();
    unsigned int dmg = statsEnemy.attackDamage;// valeur des dégats
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
    dmg=bullets.hitOrMiss(position, height, width);
    if(dmg==0)return false;
    if (stats.hp<=dmg){stats.hp=0;dead=true;} 
    else stats.hp-=dmg;
    return true;
 }

 void Player::shoot(Bullet &bullets, unsigned int nbE, Enemy* tabE)const{
    //if(nbE==0){bullets.damage=0;return;}
    Position dist=tabE[0].position-position;
    float distMin=800;
    unsigned int idMin=0;
    bool canshoot=false;
    for(unsigned int i=0; i<50;i++){
        dist=tabE[i].position-position;
        if(distMin>=dist.length() && tabE[i].isAlive){
            idMin=i;
            distMin=dist.length();
            canshoot=true;
        }
    }
    if(canshoot){
        Position speed=(tabE[idMin].position-position)/(tabE[idMin].position-position).length();
        bullets.pos=position;
        bullets.speed=speed*stats.bulletSpeed;
        bullets.damage=stats.attackDamage;
        bullets.fromPlayer=true;
    }
}

//FONCTION POUR LE SHOP ET L INVENTAIRE

Inventory& Player::getInventory() {
    return inventory;
}

unsigned int Player::getAttackWithBonus() const {
    return inventory.getTotalDamage();
}