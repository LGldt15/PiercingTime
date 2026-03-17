#include "IHM.h"

Controls getInputs(){
    Controls c;
    c.up=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    c.down=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
    c.right=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    c.left=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    c.pause=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    c.select=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
    return c;
}

