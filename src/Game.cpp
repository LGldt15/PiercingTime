#include "Game.h"
#include "Player.h"

Game::Game(){
    nbJoueur=1;
    inConfig=true;
    difficulty=0;
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



void Game::update(Controls c){
    level.update(c);
}


