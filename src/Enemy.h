#ifndef _ENEMY_H
#define _ENEMY_H

#pragma once
class Player;

//nos include
#include "Bullet.h"
#include "Inventory.h"
#include <string>

/**
 * @class   Enemy
 *
 * @brief Classe expriamnt un enemy quelconque de la carte 
 *
 * 
 */

class Enemy{
private:
    Stats stats;
    unsigned int experience;
    bool rotationSide; // utilisé dans le moveShooter
public:
    unsigned int height,width;
    unsigned int sprite;
    Position position;
    bool isAlive;
    Enemy* next;
    char type[20];

    /**
    * @brief constructeur par defaut de Enemy
    * 
    * @param health HP de l enemy
    * @param damage degat de l enemy.
    * @param a si l ennemy est vivant ou pas.
    * @param s la vitese de l enemy.
    * @param idS identifiant du sprite de l ennemy.
    * @param t type de l enemy (son nom en gros).
    */
    Enemy(int health=1,int damage=1,bool a=false,float s=0.1,int idS=0,std::string t="Caveman");
    ~Enemy();
    
    /**
    * @brief permet de se deplacer vers le jouieur 
    * 
    * @param player Position du player vers lequelle se deplacer.
    */

    void move(Position &player);
    /**
    * @brief deplacement de l ennemy de tyupe Agro 
    * 
    * @param player Position du player vers lequelle se deplacer.
    */
    void moveAgro(Position &player);
    /**
    * @brief deplacement de l ennemy de type Shooter
    * 
    * @param player Position du player vers lequelle se deplacer.
    */
    void moveShooter(Position &player);
    /**
    * @brief deplacement de l ennemy de type Deserter
    * 
    * @param player Position du player vers lequelle se deplacer.
    */
    void moveDeserter(Position &player);
    /**
    * @brief permet au enemy de typoe shooter de tirer une ball vers un joueur et la jouter a la map
    * 
    * @param bullets tableau de ball a laquelle ajouter son tir
    * @param nbP nombre de joueur sur la carte
    * @param tabP pointeur vers les joueurs (permet donc de trouver le joueur le plus proche pour tirer)
    */
    void shoot(Bullet &bullets, unsigned int nbP, Player* tabP)const;
    /**
    * @brief Permet a un ennemy de prendre les degat d une ball 
    * 
    * @param bullets balle par laquelle l ennemy doit prendre des degats.
    * @return renvoie si l ennemy a ete toucher ou pas
    */

    bool takeDamageBullet(Bullet &bullets);
    /**
    * @brief Renvoi le sprite associer a un ennemy
    * 
    * @return renvoie le sprite de l ennemy
    */
    unsigned int getSprite();
    /**
    * @brief Renvoi la position associer a un ennemy
    * 
    * @return renvoie la position de l ennemy
    */
    Position getPosition();
    /**
    * @brief Renvoi les stats associer a un ennemy
    * 
    * @return renvoie les stats de l ennemy
    */
    Stats& getStats();
    /**
    * @brief Renvoi les stats associer a un ennemy
    * 
    * @return renvoie les stats de l ennemy
    */
    const Stats& getStats()const;

};











#endif