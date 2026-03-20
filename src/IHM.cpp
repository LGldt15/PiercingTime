#include "IHM.h"
#include "Enemy.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include "iostream"


IHM::IHM(){
    sf::Vector2<unsigned int> size={800,800};
    window=sf::RenderWindow(sf::VideoMode(size), "My SFML Window");
    mapTypes[0].loadFromFile("./assets/Background.png");
    playerTypes[0].loadFromFile("./assets/player.png");
    enemyTypes[0].loadFromFile("./assets/gromgroi.png");
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

}

void IHM::renderShop() {

}

void IHM::renderMap(){
    window.clear(sf::Color::Black);
    sf::Sprite map(mapTypes[game.getMapId()]);
    sf::Vector2f size={800.0f/1200,800.0f/1200};
    map.setScale(size);
    window.draw(map);
    Player* p=game.getPlayers();
    for(int i=0;i<game.getNbJoueur();i++){
        sf::Sprite player(playerTypes[p[i].sprites]);
        sf::Vector2f pos;
        pos.x=p[i].position.posX;
        pos.y=p[i].position.posY;
        player.setPosition(pos);
        window.draw(player);
    }
    Enemy* enemyzero=game.getEnemies();
    for(int i=0;i<game.getNbEnemys();i++){
        
        sf::Sprite enemy(enemyTypes[enemyzero[i].sprite]);
        sf::Vector2u s=enemyTypes[enemyzero[i].sprite].getSize();
        sf::Vector2f si={100.0f/s.x,60.0f/s.y};
        //std::cout<<"here and si is :"<<si.x<<' '<<si.y<<std::endl;
        enemy.setScale(si);
        sf::Vector2f pos;
        pos.x=enemyzero[i].position.posX;
        pos.y=enemyzero[i].position.posY;
        enemy.setPosition(pos);
        window.draw(enemy);
    }
    
    window.display();  
}

void IHM::gameLoop(){
    while(true){
        getInputs();
        game.update(inputs);
        renderMap();
    }
}

void IHM::renderMenu() {

}

void IHM::playerSelect() {

}
