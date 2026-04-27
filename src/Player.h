#ifndef _PLAYER_H
#define _PLAYER_H

//nos include
#include "Bullet.h"
#include "Enemy.h"
#include "Inventory.h"
#include "Controls.h"


/**
 * @class Player
 * 
 * @brief classe gérant le(s) joueur(s) humain(s)
 */

class Player{
private:
    Stats stats;
    Inventory inventory;
public:
    Position position;// !!! à utiliser avec le get
    unsigned int height,width;// !!! à utiliser avec le get
    unsigned int sprites;// !!! à utiliser avec le get
    unsigned int experience;// !!! à utiliser avec le get
    unsigned int gold;// !!! à utiliser avec le get et set
    int cooldown;
    bool dead;
    bool start;

    /**
    * @brief constructeur par defaut de Player
    * 
    */
    Player();
    ~Player();

    /**
    * @brief permet au joueur de tirer une balle vers un joueur et l ajouter a la map
    * 
    * @param bullets tableau de balle a laquelle ajouter son tir
    * @param nbE nombre d ennemy sur la carte
    * @param tabE pointeur vers les ennemy (permet donc de trouver l ennemy le plus proche pour tirer)
    */
    void shoot(Bullet &bullets, unsigned int nbE, Enemy* tabE)const;
    /**
    * @brief Permet a un player de prendre les degat d une balle 
    * 
    * @param bullets balle par laquelle le player doit prendre des degats.
    * @return renvoie si le player a ete touché ou pas
    */
    bool takeDamageBullet(Bullet &bullets);
    /**
    * @brief Permet a un player de prendre les degat d une collision avec un enemy 
    * 
    * @param enemy enemy qui collisionne le player qui doit prendre des degats.
    * @return renvoie si le player a ete touché ou pas
    */
    bool takeDamage(const Enemy &enemy);
    /**
    * @brief Permet a un player de se deplacer 
    * 
    * @param c controles qui permettent de déterminer le déplacement.
    * @param winWidth dimension de la fenètre
    * @param winHeight dimension de la fenètre
    */
    void move(const Controls &c,unsigned int winWidth,unsigned int winHeight);
    /**
    * @brief Permet a un player d'incrémenter son niveau selon son experience
    */
    void levcelUP();

    /**
    * @brief Renvoie les statistiques associees a un player
    * 
    * @return renvoie les statistiques du player
    */
    Stats& getStats();
    /**
    * @brief Renvoie la position associees a un player
    * 
    * @return renvoie la position du player
    */
    Position getPosition();

    /**
    * @brief Renvoie la hauteur associee a un player
    * 
    * @return renvoie la hauteur du player
    */
    unsigned int getHeight();
    /**
    * @brief Renvoie la largeur associee a un player
    * 
    * @return renvoie la largeur du player
    */
    unsigned int getWidth();
    /**
    * @brief Renvoie l indice du sprite associe a un player
    * 
    * @return renvoie l indice du sprite du player
    */
    unsigned int getSprites();
    /**
    * @brief Renvoie l experience associe a un player
    * 
    * @return renvoie la position du player
    */
    unsigned int getExperience();
    /**
    * @brief Renvoie l or associees a un player
    * 
    * @return renvoie l or du player
    */
    unsigned int getGold();
    /**
    * @brief Renvoie l inventaire associe a un player
    * 
    * @return renvoie l inventaire du player
    */
    Inventory& getInventory();
    /**
    * @brief Modifie l or associe a un player
    * 
    * @param g valeur de gold à remplacer
    */
    void setGold(unsigned int g);

    //server managment
    /**
    * @brief Renvoie l identifiant multijoueur associe a un player
    * 
    * @return renvoie l identifiant multijoueur du player
    */
    int getIdMulti();
    /**
    * @brief Met a jour le booleen start selon les inputs de l'utilisateur.ice 
    * 
    * @param c le controle permettant de déterminer si on commence
    */
    void doWeStart(Controls c);

};


#endif
