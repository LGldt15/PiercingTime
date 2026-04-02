#include "Game.h"
#include "Player.h"
#include<iostream>

Game::Game(){
    nbJoueur=1;
    inConfig=true;
    difficulty=0;
    level=Map(0,players[0],nbJoueur);
    isShopActive =false;
    level = Map(0, players[0], nbJoueur);


    for (int i = 0; i < 4; i++)
    {
        playerShop[i]= Shop();
    }
    
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


        if (level.getNbEnemies() == 0) {
            isShopActive = true;

            for (int i = 0; i < nbJoueur; i++) {
                playerShop[i].refreshShop();
            }
        }
    } else {
        //pour le joueur 1 uniquement pour le moment

         playerShop[0].handleInput(c, players[0]);

//faire la fonction pour passer a la prochaine WAve
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