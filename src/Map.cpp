#include "Map.h"
#include "Bullet.h"
#include "Player.h"
  
#include <iostream>
  //int idMap;
  //  Player* players;
  //  int nbPlayers;
  //  Enemy* enemies;
  //  int nbEnemies;
  //  Bullet* bullets;
  //  int nbBullets;
    
Map::Map(){

    idMap=0;
    nbPlayers=0;
    nbEnemies=0;
    nbBullets=0;
}


Map::Map(int idS,Player &p,int nbP){
    idMap=idS;
    players[0]=&p;
    nbPlayers=nbP;
    nbEnemies=2;
    enemies[0]=Enemy(1,0,true,2,0);
    enemies[1]=Enemy(1,0,true,1,0);
    nbBullets=0;
    for (int i=0;i<499;i++){
        bullets[i].next=&bullets[i+1];
    }
}


void Map::move(Controls &c,unsigned int winWidth, unsigned int winHeight){
    for (int i=0;i<nbPlayers;i++){
        players[i]->move(c,winWidth, winHeight);


        for (int j=0;j<50;j++){
            if(enemies[j].isAlive)enemies[j].move(players[i]->position);

        }
    }    
    for (int i=0;i<500;i++){
        if(bullets[i].damage!=0)bullets[i].move();
    }

}


    
void Map::damageE(){
    nbEnemies=0;
    for(int i=0;i<50;i++){
        if(enemies[i].isAlive){
            for(int j=0;j<500;j++){
                if (bullets[j].damage!=0) {
                    enemies[i].takeDamageBullet(bullets[j]);
                }
            }
            nbEnemies++;
        }
    }
}

void Map::damageP(int player){
    int iter=nbEnemies;
    for(int i=0;i<iter;i++){
        if(enemies[i].isAlive){
            if(players[player]->takeDamage(enemies[i])) return;
        }
        else iter++;
    }
    iter=nbBullets;
    for(int i=0;i<iter;i++){
        if(bullets[i].damage!=0){
            if(players[player]->takeDamageBullet(bullets[i])){
                return;
            } 
        }
        else iter++;
    }
}

void Map::damageAll(){

    for(int i=0;i<nbPlayers;i++){
        damageP(i);
    }

    damageE();
}

void Map::update(Controls& c, unsigned  int winWidth, unsigned int winHeight){
    move(c, winWidth, winHeight);
    damageAll();
    for(int i=0;i<nbPlayers;i++){
        if (nbBullets<500 && players[i]->cooldown<=0){
            int k=0;
            bool kischanged=false;
            nbBullets=0;
            for(int j=0;j<500;j++){
                if (bullets[j].pos.posX<0 || bullets[j].pos.posX>800 || bullets[j].pos.posY<0 || bullets[j].pos.posY>800){
                    bullets[j].damage=0;
                    bullets[j].pos={0,0};
                    bullets[j].speed={0,0};
                }
                if (!kischanged && bullets[j].damage==0){
                    k=j;
                    kischanged=true;
                }
                if(bullets[j].damage!=0){
                    nbBullets++;
                }
            }
            if(bullets[k].damage==0){
                players[i]->shoot(bullets[k], 50, enemies);
                nbBullets++;
                players[i]->cooldown=10;
            }
        }
    }

}


int Map::getMapId(){
    return idMap;
}

int Map::getNbEnemies() {
    int alive = 0;
    for (int i = 0; i < 50; i++) { // 50 est la taille de ton tableau d'ennemis
        if (enemies[i].isAlive) {
            alive++;
        }
    }
    return alive;
}

Enemy* Map::getEnemies(){
    return &enemies[0];
}


int Map::getNbBullet(){
    return nbBullets;
}
Bullet* Map::getBullets(){
    return &bullets[0];
}