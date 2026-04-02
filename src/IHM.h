#ifndef _IHM_H
#define _IHM_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

//nos include
#include "Game.h"
#include "MainMenu.h"
#include "Player.h"



class IHM{
private:
    Game game;
    MainMenu mainMenu;
    Controls inputs;
    unsigned int winWidth;
    unsigned int winHeight;
    
    sf::Font font;


    
    sf::RenderWindow window;


    sf::Texture playerTypes[2];
    sf::Sprite *playerSprites[2];

    sf::Texture enemyTypes[4];
    sf::Sprite *enemySprites[4];

    sf::Texture mapTypes[9];//one level uses one map
    sf::Sprite *mapSprites[9];//one level uses one map


    sf::Texture bulletTypes[9];//one level uses one map
    sf::Sprite *bulletSprites[9];//one level uses one map

    sf::Texture itemTypes[20];
    sf::Texture collectibles;

    sf::Texture buttons[10];
    sf::Sprite *buttonSprites[10];

    sf::Texture ui[10];
public:
    IHM();
    ~IHM();
    void renderShop();
    void renderMap();
    void renderMenu();
    void playerSelect();
    //utilitaire
    void getInputs();
    //loop
    void gameLoop();
    //tout
    void app();

    void handleShopInput();

};



#endif