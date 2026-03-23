#include "Map.h"
#include "Player.h"
  
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
    nbEnemies=0;
    nbEnemies=1;
    enemies[0]=Enemy(1,0,true,0.05,0);
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
        if(bullets[0].damage!=0){
            players[i]->shoot(bullets[0], nbEnemies, enemies);
        }
        if(nbBullets<500){
            players[i]->shoot(*bullets[0].next, nbEnemies, enemies);
            bullets[0].next=bullets[0].next->next;
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