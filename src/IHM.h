#ifndef _IHM_H
#define _IHM_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

//nos include
#include "Game.h"
#include "MainMenu.h"



class IHM{
private:
    Game game;
    MainMenu mainMenu;

    sf::Texture playerTypes[2];
    sf::Texture enemyTypes[4];
    sf::Texture mapTypes[9];//one level uses one map
    sf::Texture itemTypes[20];
    sf::Texture collectibles;
    sf::Texture buttons[10];
    sf::Texture ui[10];
public:
    IHM();
    ~IHM();
    void renderShop(Shop shop,Player* players,int nbPlayers) const;
    void renderMap(Map level) const;
    void renderUI(MainMenu ui) const;
    void playerSelect(Player* players,int nbPlayers) const;
    Controls getInputs();

};



#endif