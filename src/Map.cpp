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
    std::cout<<"pre\n";
    for(int i=0;i<50;i++){
        if(enemies[i].isAlive){
            for(int j=0;j<500;j++){
                if (bullets[j].damage!=0) {
                    enemies[i].takeDamageBullet(bullets[j]);
                }
            }
        }
    }
    std::cout<<"post\n";
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
    std::cout<<"dasn damage PLayer\n";
    for(int i=0;i<nbPlayers;i++){
        damageP(i);
    }
    std::cout<<"dasn damageE\n";
    damageE();
}

void Map::update(Controls& c){
    std::cout<<"avant move\n";
    move(c);
    std::cout<<"avant damage\n";
    damageAll();
    std::cout<<"avant bullets\n";
    for(int i=0;i<nbPlayers;i++){
        if (nbBullets<500 && players[i]->cooldown<=0){
            std::cout<<"pas dasn tir 0\n";
            int k=0;
            for(int j=0;j<500;j++){
                std::cout<<"dasn els tests\n";
                if (bullets[j].pos.posX<0 || bullets[j].pos.posX>800 || bullets[j].pos.posY<0 || bullets[j].pos.posY>800){
                    bullets[j].damage=0;
                    bullets[j].pos={0,0};
                    bullets[j].speed={0,0};
                    nbBullets--;
                }
                if (bullets[k].damage!=0 && bullets[j].damage==0){
                    k=j;
                }
            }
            std::cout<<"dasn le tir\n";
            if(bullets[k].damage==0){
                std::cout<<"avant le tir"<<nbEnemies<<std::endl;
                players[i]->shoot(bullets[k], nbEnemies, enemies);
                std::cout<<"apres tir (avant nbbullets++)\n";
                nbBullets++;
                std::cout<<"avant modif cooldown\n";
                players[i]->cooldown=1000;
            }
            std::cout<<"apres tire pas 0\n";
        }
    }
    std::cout<<"apres bullets\n";
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