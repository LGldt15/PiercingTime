#ifndef _GAME_H
#define _GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
///lib 
#include "Enemy.h"
#include "Player.h"
#include "Inventory.h"



class Game{
private:
    Player players[4];
    Inventory inventory[4];
    unsigned int nbJoueur;
    Enemy enemies[50];
    int nbEnemies;
    Bullet bullets[500];
    int nbBullet;
    sf::Sprite* levels;
    unsigned int level;
    unsigned int difficulty;
public:
    Game(sf::Texture &t,sf::Texture &playerSprites);
    ~Game();
    ///menu stuff (before game starts)
    void addPlayer();
    void removePlayer();
    void renderMenu(sf::RenderWindow &window);
    bool setup(sf::RenderWindow &window);
    ///in game stuff
    void startGame();
    void render(sf::RenderWindow &window) const;//sera appeler dans gameLoop
    void damagePlayers(int player);
    void damageEnemies();
    void damageAll();
    void wave();
    void shop();
    void gameLoop(sf::RenderWindow &window);
};

#endif