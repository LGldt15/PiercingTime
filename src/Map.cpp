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
    enemies[0]=Enemy(1,0,true,0.05,0);
    enemies[1]=Enemy(1,0,true,0.05,0);
    nbBullets=0;
    for (int i=0;i<499;i++){
        bullets[i].next=&bullets[i+1];
    }
}


void Map::move(Controls &c){
    for (int i=0;i<nbPlayers;i++){
        players[i]->move(c);
        for (int j=0;j<nbEnemies;j++){
            enemies[j].move(players[i]->position);
        }
    }    
    for (int i=0;i<nbBullets;i++){
        bullets[i].move();
    }

}


    
void Map::damageE(){
    int iter=nbEnemies;
    for(int i=0;i<iter;i++){
        if(enemies[i].isAlive){
            int iterBullet=nbBullets;
            for(int j=0;j<iterBullet;j++){
                if (bullets[j].damage==0) iterBullet++;
                enemies[i].takeDamageBullet(bullets[j]);
                if(!enemies[i].isAlive){
                    enemies[i].next=enemies[0].next;
                    enemies[0].next=&enemies[i];
                }
            }
        }
        else iter++;
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
                bullets[i].next=bullets[0].next;
                bullets[0].next=&bullets[i];
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

void Map::update(Controls& c){
    move(c);
    damageAll();
    for(int i=0;i<nbPlayers;i++){
        if(bullets[0].damage==0 && players[i]->cooldown<=0){
            std::cout<<"modified bullet 0\n";
            players[i]->shoot(bullets[0], nbEnemies, enemies);
            nbBullets++;
            players[i]->cooldown=1000;
            std::cout<<"finished byullet 0\n";
        }
        else if (nbBullets<500 && players[i]->cooldown<=0 && bullets[0].next!=nullptr){
            std::cout<<"modified bullet not 0\n";
            int k=0;
            for(int j=0;j<500;j++){
                if (bullets[k].pos.posX<0 || bullets[k].pos.posX>800 || bullets[k].pos.posY<0 || bullets[k].pos.posY>800){
                    bullets[k].damage=0;
                    bullets[k].pos={0,0};
                    bullets[k].speed={0,0};
                    k--;
                    nbBullets--;
                }
                if (bullets[k].damage!=0){
                    k++;
                }
            }
            players[i]->shoot(bullets[k], nbEnemies, enemies);
            nbBullets++;
            players[i]->cooldown=1000;
            for (int i=0;i<nbBullets;i++){
                std::cout<<bullets[i].pos.posX<<' '<<bullets[i].pos.posY<<' '<<i<<std::endl;
            }
        }
    }

}

int Map::getMapId(){
    return idMap;
}
int Map::getNbEnemies(){
    return nbEnemies;
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