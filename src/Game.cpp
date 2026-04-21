#include "Game.h"
#include "Player.h"
#include <iostream>

Game::Game(){
    nbJoueur=1;
    inConfig=true;
    difficulty=0;
    level=Map(0,players[0],nbJoueur);
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
        for(int i=0;i<nbJoueur;i++){
            players[i].move(c, winWidth, winHeight);
        }
        if (level.getNbEnemies() == 0) {
            std::cout << "SHOP" << std::endl; 
            isShopActive = true;
            playerShop[0].refreshShop();
        }
        level.update(winWidth, winHeight,players,nbJoueur);
}

void Game::update(Controls *c){
    players[0].doWeStart(c[0]);
    if(players[0].start){
        for(int i=0;i<nbJoueur;i++){
            players[i].move(c[i], 800,800);
        }
        level.update(800,800,players,nbJoueur);
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
    return players[i].sprites;
}

Bullet* Game::getBullets(){
    return level.getBullets();
}
int Game::getNbBullets(){
    return level.getNbBullet();
}