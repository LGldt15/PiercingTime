#include "IHM.h"

void IHM::getInputs(){
    inputs.up=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    inputs.down=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
    inputs.right=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    inputs.left=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    inputs.pause=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
    inputs.select=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
}

