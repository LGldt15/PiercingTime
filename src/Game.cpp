#include "Game.h"
#include "Player.h"
#include <iostream>

Game::Game(){
    nbJoueur=1;
    inConfig=true;
    difficulty=0;
    level=Map(0,players[0],nbJoueur);
    players[0].setGold(200);
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



void Game::update(Controls c,  unsigned int winWidth, unsigned int winHeight){
    if (!isShopActive) {
        level.update(c, winWidth, winHeight);

        std::cout << "Ennemies left : " << level.getNbEnemies() << std::endl;


        if (level.getNbEnemies() == 0) {
            std::cout << "SHOP" << std::endl; 
            isShopActive = true;
            playerShop[0].refreshShop();
        }
    } else {
        playerShop[0].handleInput(c, players[0]);
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