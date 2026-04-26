#ifndef _BULLET_H
#define _BULLET_H
#include "Position.h"


/**
 * @class Bullet
 *
 * @brief une classe pour gerer les balles tirer par enemies et joueur
 *
 * Une classe pour illustrer l'utilisation de Doxygen pour générer de la documentation.
 */

class Bullet{
private: // composantes en x et y du vecteur vitesse
    unsigned int sprite;
public:
    Position speed;
    Position pos;
    bool fromPlayer;//true: viens d'un joueur , false: viens d'un ennemy
    unsigned int damage;

    /**
    * @brief Constructeur par defaut
    * 
    */

    Bullet();
   
    /**
    * @brief Constructeur avec parametre de bullet
    * 
    * @param p position de la bullet a t=0
    * @param s vitesse de la balle
    * @param d degat fait par la balle
    * @param fP boolein pour savoir si la balle fait des degat au joueur ou au enemy
    * @return Description de la valeur de retour.
    */

    Bullet(Position p,Position S,unsigned int d,bool fP);
    ~Bullet();

    /**
     * @brief regarde si une balle touche un enemy en fonction de sa position et de sa taille
     * 
     * @param min position minimal de la cible
     * @param max position maximale de la cible
     * @return renvoie les degat fait 0 sinon
     */

    unsigned int hitOrMiss(Position min,Position max);//renvoie les degat fait un une entite en foncion de la hitbpx de celle ci(xMin et yMin)

    /**
     * @brief deplace la balle grave a ca vitesse
     */
    void move();
    /**
     * @brief revoie l identifiant du sprite de la balle (permet de la remonter jusqua l'ihm pour l affichage)
     *
     * @return renvoie l id de son sprite
     */
    int getSprite();
};









#endif