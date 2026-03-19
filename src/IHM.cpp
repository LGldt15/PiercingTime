#include "IHM.h"



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


void IHM::renderShop() const{

}

void IHM::renderMap() const{

}

void IHM::renderMenu() const{

}

void IHM::playerSelect() const{

}
