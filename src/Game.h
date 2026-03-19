#ifndef _GAME_H
#define _GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
///lib 
#include "Enemy.h"
#include "Player.h"
#include "Inventory.h"
#include "Map.h"


class Game{
private:
    Player players[4];
    Inventory inventory[4];
    unsigned int nbJoueur;
    bool inConfig;

    Map level;
    unsigned int difficulty;
    
public:
    Game(sf::Texture &t,sf::Texture &playerSprites);
    ~Game();
    ///menu stuff (before game starts)
    void addPlayer();
    void removePlayer();
    void renderMenu();
    bool setup();
    ///in game stuff
    void update();
};

#endif