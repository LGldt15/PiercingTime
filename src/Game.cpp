#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>

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
    if (!isShopActive) {


        std::cout << "Ennemies left : " << level.getNbEnemies() << std::endl;


        if (level.getNbEnemies() == 0) {
            std::cout << "SHOP" << std::endl; 
            isShopActive = true;
            for(int i=0;i<nbJoueur;i++){
                playerShop[i].refreshShop();
            }
        }
        for(int i=0;i<nbJoueur;i++){
            players[0].move(c, 800, 800);
        }
        level.update(800,800,players,nbJoueur);
    } else {
        playerShop[0].handleInput(c, players[0]);
    }
}

void Game::update(Controls *c){
    if (!isShopActive) {

        std::cout << "Ennemies left : " << level.getNbEnemies() << std::endl;

        for(int i=0;i<nbJoueur;i++){
            players[i].move(c[i], 800, 800);
        }
        level.update(800,800,players,nbJoueur);
        if (level.getNbEnemies() == 0) {
            std::cout << "SHOP" << std::endl; 
            isShopActive = true;
            for(int i=0;i<nbJoueur;i++){
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
    return players[i].sprites;
}

Bullet* Game::getBullets(){
    return level.getBullets();
}
int Game::getNbBullets(){
    return level.getNbBullet();
}