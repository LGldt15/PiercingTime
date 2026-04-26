#include "Map.h"
#include "Bullet.h"
#include "Player.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include "json.hpp"



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

    


    std::ifstream file("../assets/config/waves.json"); 
        if (file.is_open()) {
    std::cout << "Fichier JSON trouvé avec succès !" << std::endl;
        } else {
    std::cerr << "Erreur : Impossible de trouver le fichier JSON !" << std::endl;
    }
}


Map::Map(int idS,Player &p,int nbP){
    idMap=idS;
    players[0]=&p;
    nbPlayers=nbP;
    nbEnemies=6;


    timer = 0.0f;
    waveID = 1;
    dead = false;

    for(int i = 0; i < MAX_ENEMY; i++){
        enemies[i].isAlive = false;
    }

    enemies[0]=Enemy(1,0,true,10,2,0);
    enemies[1]=Enemy(1,0,true,10,1,0);
    enemies[2]=Enemy(1,0,true,10,1,0);
    enemies[3]=Enemy(1,0,true,10,1,0);
    enemies[4]=Enemy(1,0,true,10,1,0);
    enemies[5]=Enemy(1,0,true,10,1,0);
    nbBullets=0;
    //for (int i=0;i<MAX_BULLETS-1;i++){
    //    bullets[i].next=&bullets[i+1];
    //}


   // startWave();

}

void Map::startWave(){
    int count = 5 + (waveID * 2); 
    if (count > MAX_ENEMY) count = MAX_ENEMY;


    for(int i = 0; i < count; i++) {

        int type = (waveID % 2 == 0) ? 1 : 0; 
        enemies[i] = Enemy(type, 0, true, 2, 0); 
    }

    //std::cout << "wave" << waveID << std::endl;
    

    waveID++;
}




    
void Map::move(Player* players,int nbPlayers){
    for (int i=0;i<nbPlayers;i++){
        for (int j=0;j<50;j++){
            if(enemies[j].isAlive)enemies[j].move(players[i].position);

        }
    }    
    for (int i=0;i<500;i++){
        if(bullets[i].damage!=0)bullets[i].move();
    }

}

void Map::move(unsigned int winWidth, unsigned int winHeight,Player* players,int nbPlayers){
    for (int i=0;i<nbPlayers;i++){
        for (int j=0;j<50;j++){
            if(enemies[j].isAlive)enemies[j].move(players[i].position);

        }
    }    
    for (int i=0;i<500;i++){
        if(bullets[i].damage!=0)bullets[i].move();
    }

}


    
int Map::damageE(){
    nbEnemies = 0; 
    int gold=0;
    for(int i = 0; i < MAX_ENEMY; i++){
        if(enemies[i].isAlive){
            for(int j = 0; j < MAX_BULLETS; j++){
                if (bullets[j].damage != 0) {
                    enemies[i].takeDamageBullet(bullets[j]);
                }

            }
            if(!enemies[i].isAlive){
                gold += enemies[i].getGold();
            }
            nbEnemies++; 
        }
    }
    return gold;
}

void Map::damageP(Player* players,int nbPlayers , int player){
    for(int i=0;i<MAX_ENEMY;i++){
        if(enemies[i].isAlive){
            if(players[player].takeDamage(enemies[i])) return;
        }
    }
    for(int i=0;i<MAX_BULLETS;i++){
        if(bullets[i].damage!=0){
            if(players[player].takeDamageBullet(bullets[i])){
                return;
            } 
        }
    }
}

void Map::damageAll(Player* players,int nbPlayers){
    int g=damageE();

    for(int i=0;i<nbPlayers;i++){
        damageP(players,nbPlayers,i);
        players[i].setGold(players[i].getGold()+g/nbPlayers);
    }

}


//systeme waves

void Map::loadWaves(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "ERREUR : Impossible d'ouvrir " << filename << std::endl;
        return;
    }

    nlohmann::json j;
    try {
        file >> j;
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "ERREUR JSON : " << e.what() << std::endl;
        return;
    }

    nbWaves = 0; // Réinitialisation propre
    if (j.contains("waves")) {
        for (auto& w : j["waves"]) {
            if (nbWaves >= MAX_WAVES) break;

            waves[nbWaves].triggerTime = w.value("time", 0.0f);
            waves[nbWaves].triggered = false;
            waves[nbWaves].nbTypes = 0;

            if (w.contains("enemies")) {
                for (auto& e : w["enemies"]) {
                    if (waves[nbWaves].nbTypes >= MAX_TYPES_PER_WAVE) break;

                    EnemySpawnData& data = waves[nbWaves].enemyTypes[waves[nbWaves].nbTypes];
                    
                    std::string typeStr = e.value("type", "Rabbit");
                    strncpy(data.type, typeStr.c_str(), 31);
                    data.type[31] = '\0'; 

                    data.count = e.value("count", 1);
                    data.hp = e.value("hp", 10);
                    data.dmg = e.value("dmg", 5);
                    data.speed = e.value("speed", 2.0f);
                    data.spriteId = e.value("sprite", 0);

                    waves[nbWaves].nbTypes++;
                }
            }
            
            // C'EST CETTE LIGNE QUI MANQUAIT ! 
            // Sans elle, ton jeu pense qu'il n'y a aucune vague.
            nbWaves++; 
        }
    }
    
    std::cout << "DEBUG : " << nbWaves << " vagues chargées avec succès." << std::endl;
}

void Map::update(unsigned  int winWidth, unsigned int winHeight,Player* players,int nbPlayers,float time ){
    timer += time;


    for (int i = 0; i < nbWaves; i++) {
        if (!waves[i].triggered && timer >= waves[i].triggerTime) {
            

            for (int t = 0; t < waves[i].nbTypes; t++) {
                EnemySpawnData& e = waves[i].enemyTypes[t];
                
                for (int c = 0; c < e.count; c++) {
                    for (int slot = 0; slot < MAX_ENEMY; slot++) {
                        if (!enemies[slot].isAlive) {
                            enemies[slot] = Enemy(e.hp, e.dmg, true, e.speed, e.spriteId, e.type);
                            break; 
                        }
                    }
                }
            }
            waves[i].triggered = true;
        }
    }

    move(winWidth, winHeight,players,nbPlayers);
    damageAll(players,nbPlayers);
    for(int i=0;i<nbPlayers;i++){
        if (nbBullets<500 && players[i].cooldown<=0){
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
                players[i].shoot(bullets[k], 50, enemies);
                nbBullets++;
                players[i].cooldown=10;
            }
        }
    }
}


int Map::getMapId(){
    return idMap;
}

int Map::getNbEnemies() {
    int alive = 0;
    for (int i = 0; i < MAX_ENEMY; i++) { // 50 est la taille de ton tableau d'ennemis
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


bool Map::isDead() { return dead; }

void Map::restart() {
    timer = 0.0f; // Reset horloge
    
    for(int i = 0; i < nbWaves; i++) {
        waves[i].triggered = false;
    }
    
    for(int i = 0; i < MAX_ENEMY; i++) {
        enemies[i].isAlive = false;
    }
    
    std::cout << "DEBUG : Reset effectué. Timer = 0. Vagues réarmées." << std::endl;
}


void Map::resetWaves() {
    timer = 0.0f;
    for (int i = 0; i < nbWaves; i++) {
        waves[i].triggered = false; 
    }
    std::cout << "DEBUG : Vagues réarmées pour la nouvelle manche." << std::endl;
}

bool Map::allWavesFinished(int nbEnemies) const {
    for (int i = 0; i < nbWaves; i++) {
        if (!waves[i].triggered) return false; 
    }
    

    if (nbEnemies > 0) return false;

    return true;
}