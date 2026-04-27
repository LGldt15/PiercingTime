#include "Game.h"
#include "Player.h"
#include <iostream>

Game::Game(){
    nbJoueur=1;
    inConfig=true;
    difficulty=0;
    level=Map(0);
    players[0].setGold(0);
    isShopActive=false;
    level.loadWaves("assets/config/waves.json");
}

Game::~Game(){

}

int Game::getNbJoueur(){
    return nbJoueur;
}

Player* Game::getPlayers(){
    return &players[0];
}

void Game::setNbPlayers (int i){
    nbJoueur=i;
}





void Game::update(Controls c,  unsigned int winWidth, unsigned int winHeight,float time){
    if (!isShopActive) {
        //std::cout << "Ennemies left : " << level.getNbEnemies() << std::endl;
        if (level.allWavesFinished(level.getNbEnemies()) && level.getTimer() > 2.0f) { 
    std::cout << "SHOP OUVERT" << std::endl; 
    isShopActive = true;
    for(int i=0; i < nbJoueur; i++) {
        playerShop[i].refreshShop();
    }
}
        for(int i=0;i<nbJoueur;i++){
            players[0].move(c, 800, 800);
        }
        //std::cout<<"BEFORE LEVEL UPDATE\n";
        level.update(800,800,players,nbJoueur,time);
        //std::cout<<"AFTER LEVEL UPDATE\n";
    }else{
        if(c.next){
            isShopActive = false; 
            level.restart();
        }
        playerShop[0].handleInput(c, players[0]);
    }
}


void Game::update(Controls *c, float time){
    if (!isShopActive) {

        //std::cout << "Ennemies left : " << level.getNbEnemies() << std::endl;

        for(int i=0;i<nbJoueur;i++){
            players[i].move(c[i], 800, 800);
        }
        level.update(800,800,players,nbJoueur,time);
        if (level.allWavesFinished(level.getNbEnemies()) && level.getTimer() > 2.0f) { 
    std::cout << "SHOP OUVERT" << std::endl; 
    isShopActive = true;
    for(int i=0; i < nbJoueur; i++) {
        playerShop[i].refreshShop();
    }
    }
    } else {
        for(int i=0;i<nbJoueur;i++){
            playerShop[i].handleInput(c[i], players[i]);
        }
    }
}

Enemy* Game::getEnemies(){
    return level.getEnemies();
}
int Game::getNbEnemys(){
    return level.getNbEnemies();
}

int Game::getMapId(){
    return level.getMapId();
}

int Game::getPlayerId(int i){
    return players[i].getSprites(); 
}

Bullet* Game::getBullets(){
    return level.getBullets();
}
int Game::getNbBullets(){
    return level.getNbBullet();
}


bool Game::isTimeUp() {

    return level.isTimeUp(); 
}

bool Game::isPlayerDead() {


    return players[0].getStats().hp <= 0; 
}

void Game::resetTimer() {
    level.resetTimer();
}

void Game::restart(){
    level.restart();
}