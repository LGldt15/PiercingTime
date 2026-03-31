#include "Game.h"
#include "Player.h"

Game::Game(){
    nbJoueur=0;
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
    level.update(winWidth, winHeight,players,nbJoueur);
}

void Game::update(){
    level.update(players,nbJoueur);
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