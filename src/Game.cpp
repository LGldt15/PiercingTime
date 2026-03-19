#include "Game.h"
#include "Player.h"
#include <iostream>

Game::Game(sf::Texture &t,sf::Texture &playerSprites){
    nbJoueur=1;
    level=0;
    difficulty=1;
    levels=new sf::Sprite(t);//on mettera toute les texture ici pour les niveau
    sf::Vector2u scale=t.getSize();
    float scaleX=800.f/scale.x;
    float scaleY=800.f/scale.y;
    sf::Vector2<float> newScale={scaleX,scaleY};
    levels[0].setScale(newScale);
    //ici on gerera les sprite et la creation du joueur de base
    players[0]=Player(playerSprites);
    for (int i=0;i<49;i++){
        enemies[i].next=&enemies[i+1];
    }   
    for (int i=0;i<499;i++){
        bullets[i].next=&bullets[i+1];
    }
    std::cout<<"Game construit\n";
    for (int i=0;i<50;i++){
        enemies[i].isAlive=true;
    }
}

Game::~Game(){
    delete [] levels;
}

void Game::render(sf::RenderWindow &window) const{

    window.clear();
    window.draw(levels[level]);
    players[0].render(window);
    for (int j=0;j<50;j++){
        if(enemies[j].isAlive)enemies[j].render(window);
    }
    window.display();
}


void Game::damagePlayers(int player){
    int iter=nbEnemies;
    for(int i=0;i<iter;i++){
        if(enemies[i].isAlive){
            if(players[player].takeDamage(enemies[i])) return;
        }
        else iter++;
    }
    iter=nbBullet;
    for(int i=0;i<iter;i++){
        if(bullets[i].damage!=0){
            if(players[player].takeDamageBullet(bullets[i])){
                bullets[i].next=bullets[0].next;
                bullets[0].next=&bullets[i];
                return;
            } 
        }
        else iter++;
    }
}

void Game::damageEnemies(){
    int iter=nbEnemies;
    for(int i=0;i<iter;i++){
        if(enemies[i].isAlive){
            int iterBullet;
            for(int j=0;j<iterBullet;j++){
                if (bullets[j].damage==0) iterBullet++;
                enemies[i].takeDamageBullet(bullets[j]);
                if(!enemies[i].isAlive){
                    enemies[i].next=enemies[0].next;
                    enemies[0].next=&enemies[i];
                }
            }
        }
        else iter++;
    }
}

void Game::damageAll(){
    for(int i=0;i<nbJoueur;i++){
        damagePlayers(i);
    }
    damageEnemies();

}



void Game::gameLoop(sf::RenderWindow &window){
    //load toute les de texture de monstre des que on les aura
    

    //check si tt le monde est mort ou pas
    bool end=true;
    while (end && window.isOpen()){
        end=false;
        for (unsigned int i=0;i<nbJoueur;i++){
            players[i].move();
            if (!players[i].dead()){
                end=true;
            }
            for (unsigned int j=0;j<50;j++){
                if(enemies[j].isAlive)
                enemies[j].move(players[i].getPos());
            }
        }
        render(window);
    }
}
