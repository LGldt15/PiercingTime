#include "IHM.h"
#include "Enemy.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>



IHM::IHM(){
    sf::Vector2<unsigned int> size={1200,1200};
    window=sf::RenderWindow(sf::VideoMode(size), "My SFML Window");
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
        sf::Vector2f pos;
        pos.x=enemyzero[i].position.posX;
        pos.y=enemyzero[i].position.posY;
        enemy.setPosition(pos);
        window.draw(enemy);
    }
    
    window.display();  
}

void IHM::renderMenu() {

}

void IHM::playerSelect() {

}
