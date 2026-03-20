#include "IHM.h"
#include "Enemy.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include "../assets/Background.h"
#include "../assets/gromgroi.h"
#include "../assets/player.h"
//#include "iostream"


IHM::IHM(){
    sf::Vector2<unsigned int> size={800,800};
    window=sf::RenderWindow(sf::VideoMode(size), "My SFML Window");

    mapTypes[0].loadFromMemory(Background_png,Background_png_len);
    mapSprites[0]=new sf::Sprite(mapTypes[0]);

    sf::Vector2f sizeM={800.0f/1200,800.0f/1200};
    mapSprites[0]->setScale(sizeM);

    playerTypes[0].loadFromMemory(player_png,player_png_len);
    playerSprites[0]=new sf::Sprite(playerTypes[0]);

    enemyTypes[0].loadFromMemory(gromgroi_png,gromgroi_png_len);
    enemySprites[0]=new sf::Sprite(enemyTypes[0]);

}

void IHM::getInputs(){
    inputs.up=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    inputs.down=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
    inputs.right=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    inputs.left=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    inputs.pause=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
    inputs.select=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
}

IHM::~IHM(){
    for (int i=0;i<2;i++){
        if(playerSprites[i]!=nullptr)delete playerSprites[i];
        
    }
    for (int i=0;i<4;i++){
        if(enemySprites[i]!=nullptr)delete enemySprites[i];
    }
        for (int i=0;i<9;i++){
        if(mapSprites[i]!=nullptr)delete mapSprites[i];
    }
}

void IHM::renderShop() {

}

void IHM::renderMap(){
    window.clear(sf::Color::Black);
    window.draw(*mapSprites[0]);
    Player* p=game.getPlayers();
    for(int i=0;i<game.getNbJoueur();i++){
        sf::Vector2f pos;
        pos.x=p[i].position.posX;
        pos.y=p[i].position.posY;
        playerSprites[0]->setPosition(pos);
        window.draw(*playerSprites[0]);
    }
    Enemy* enemyzero=game.getEnemies();
    for(int i=0;i<game.getNbEnemys();i++){
        sf::Vector2u s=enemyTypes[enemyzero[i].sprite].getSize();
        sf::Vector2f si={100.0f/s.x,60.0f/s.y};
        //std::cout<<"here and si is :"<<si.x<<' '<<si.y<<std::endl;
        enemySprites[0]->setScale(si);
        sf::Vector2f pos;
        pos.x=enemyzero[i].position.posX;
        pos.y=enemyzero[i].position.posY;
        enemySprites[0]->setPosition(pos);
        window.draw(*enemySprites[0]);
    }
    
    window.display(); 
}

void IHM::gameLoop(){
    while (window.isOpen()){
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        getInputs();
        game.update(inputs);
        renderMap();
    }
}

void IHM::renderMenu() {

}

void IHM::playerSelect() {

}
