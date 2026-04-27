#ifndef _GAME_H
#define _GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
///lib 
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Inventory.h"
#include "Map.h"
#include "Shop.h"

/**
 * @class Game
 *
 * @brief Le jeu. gere les ennemy a travers map les joueur al difficulte les shop tout se qui est pas le menu principale
 *
 */

class Game{
private:
   Inventory inventory[4];
    unsigned int nbJoueur;


    Map level;
    unsigned int difficulty;

    //PARTIE shop 
    Player players[4];
    Shop playerShop[4]; // un shop pour chaque joueur
    bool isShopActive;



public:
    bool inConfig;//pour savoir si on affiche l ajou de joueur ou le jeu
    /**
    * @brief Constructeur par defaut de Game
    *
    */
    Game();
    /**
    * @brief Destructeur par defaut de Game
    *
    */
    ~Game();
    //utilistaire
    /**
    * @brief Renvoie le nombre de joueur dans la partie
    *
    * @return le nombre de joueur 
    */
    int getNbJoueur();
    /**
    * @brief renvoie le tableau des joueur (l adresse du tableau) cette focntion est a utilise avec getNbJoueur
    *
    * @return l adresse memoir de players[0]
    */
    Player* getPlayers();
    ///menu stuff (before game starts)
    /**
    * @brief permet de modifier le nombre de joueurs
    *
    * @param i nombre de joueur a mettre
    */
    void setNbPlayers(int i);
    ///in game stuff
    /**
    * @brief met a jour game l equivalent des calculs a faire pour calculer 1 frame du jeu
    *
    * @param c control de l unique joueur a gerer
    * @param winWidth largeur de l ecran (permet de bloquer le deplacement des joueur et des enmey au jeu)
    * @param winHeight largeur de l ecran (permet de bloquer le deplacement des joueur et des enmey au jeu)
    * @param time le descend a level pour update les map et donc les waves
    */
    void update(Controls c, unsigned int winWidth, unsigned int winHeight, float time);
    /**
    * @brief met a jour game l equivalent des calculs a faire pour calculer 1 frame du jeu mais en version serveur
    *
    * @param c pointeur vers les controls des joueur 
    * @param time le descend a level pour update les map et donc les waves
    */
    void update(Controls *c, float time);
    //get stuff for rendering
    /**
    * @brief renvoie l id du sprite de la map en cours 
    *
    * @return l id du sprite de la carte
    */
    int getMapId(); 
    /**
    * @brief renvoie renvoie le nombre d ennemies sur la carte a un instant T 
    *
    * @return le nombre d enemies
    */
    int getNbEnemys();
    /**
    * @brief renvoie les enemies de map pour les monter a l IHM pour le rendering (a utiliser avec getNbEnemys)
    *
    * @return pointeur vers les enemie de la carte
    */
    Enemy* getEnemies();

    /**
    * @brief renvoie l id du sprite d un joueur specifier
    *
    * @param i numero du joueur a qui on veux l id du sprite
    * @return l id du sprite du joueur
    */
    int getPlayerId(int i);
    /**
    * @brief renvoie renvoie le nombre de bullet sur la carte a un instant T 
    *
    * @return le nombre de bullet
    */
    int getNbBullets();
    /**
    * @brief renvoie les bullet de map pour les monter a l IHM pour le rendering (a utiliser avec getNbBullets)
    *
    * @return pointeur vers les bullet de la carte
    */
    Bullet* getBullets();

    /**
    * @brief permet de preciser a l IHM si on est dans une phase de shop ou pas
    *
    * @return l etat du shop
    */
    bool isInShop() const { return isShopActive; }
    /**
    * @brief permet de mettre le shop a actif
    *
    * @param l etant vers lequelle mettre le shop
    */
    void setShopActive(bool active) { isShopActive = active; }

    //recup l idex du shop du joueur
    /**
    * @brief renvoie l adresse du shop d un joueur
    *
    * @param playerIndex l id du joueur a qui on veux l inventire
    * @return le shop d un joueur
    */
    Shop& getShop(int playerIndex) { return playerShop[playerIndex]; }
    /**
    * @brief renvoie si une vague est finie ou pas
    *
    * @return si le temps est fini
    */
    bool isTimeUp();     
    /**
    * @brief renvoie si tout les joueur sont mort
    *
    * @return un bool qui indique l etat de tout les joueur
    */
    bool isPlayerDead();
    /**
    * @brief remet le timer d un niveau
    *
    */
    void resetTimer();
    /**
    * @brief relance un niveau
    *
    */
    void restart(); //reconstruit
};

#endif