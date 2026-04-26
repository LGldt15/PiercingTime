#ifndef _IHM_H
#define _IHM_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

//nos include
#include "Game.h"
#include "MainMenu.h"
#include "Player.h"


/**
 * @class IHM
 *
 * @brief Class de controle d une partie qu elle soit en ligne ou en locale ainsi que toute l application en generale
 *
 * Une classe pour illustrer l'utilisation de Doxygen pour générer de la documentation.
 */

class IHM{
private:
    Game game;
    MainMenu mainMenu;
    Controls inputs[4];
    unsigned int winWidth;
    unsigned int winHeight;
    //COOLDOWN PR LE SHOP 
    sf::Clock shopClock;
    //COOLDOWN pour le main menu
    private:
    sf::Clock menuClock;

    //clock pour les waves
    sf::Clock gameClock;

    //inventaire
    bool showInventory;
    
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

    sf::Texture ui[10];

    int idMulti=0;
public:
    /**
    * @brief Constructeur par defaut de IHM
    * 
    */
    IHM();
    /**
    * @brief Destructeurr par defaut de IHM
    * 
    */
    ~IHM();
    void init();
    void renderShop();
    /**
    * @brief Fonction pour afficherLa caret durant les round
    * 
    */
    void renderMap();

    /**
    * @brief Fonction pour afficher le Menu principale au lancement d3e l application
    * 
    */
    void renderMenu();
    void playerSelect();
    //utilitaire
    /**
    * @brief Fonction pour recuperer les inputs fait par les joueurs
    * 
    */
    void getInputs();
    //loop
    /**
    * @brief Fonction qui gere une partie entiere 
    * 
    */
    void gameLoop();
    /**
    * @brief Fonction qui gere une partie en mode online
    * 
    */
    void gameLoopMulti();
    /**
    * @brief fonction de gestion des inputs lors que l on est dasn un shop
    * 
    */
    void handleShopInput();
    /**
    * @brief Fonction permettan d arfficher l inventaire des joueur en partie
    *
    * @param startX position de l inventaire en x 
    * @param startY position de l inventaire en y 
    */
    void drawInventoryOverlay(float startX, float startY);
    //tout
    /**
    * @brief Fonction de l application gere tout en se servant des autre fonctions
    * 
    */
    void app();

};



#endif