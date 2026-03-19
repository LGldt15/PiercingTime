#include "Map.h"
#include "Player.h"
  
  int idMap;
    Player* players;
    int nbPlayers;
    Enemy* enemies;
    int nbEnemies;
    Bullet* bullets;
    int nbBullets;
    
Map::Map(){
    idMap=0;
    players=nullptr;
    nbPlayers=0;
    nbEnemies=0;
    nbBullets=0;
}


Map::Map(int idS,Player &p,int nbP){
    idMap=idS;
    players=&p;
    nbPlayers=nbP;
    nbEnemies=0;
    nbBullets=0;
}


void Map::move(Controls &c){
    for (int i=0;i<nbPlayers;i++){
        players[i].move(c);
        for (int i=0;i<nbEnemies;i++){
            enemies[i].move(players[i].position);
        }
    }    
    for (int i=0;i<nbBullets;i++){
        bullets[i].move();
    }

}


    
    void damageE();
    void damageP();
    void damageAll();

    void update();

int Map::getNbEnemies(){
    return nbEnemies;
}
Enemy* Map::getEnemies(){
    return &enemies[0];
}