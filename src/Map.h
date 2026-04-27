#ifndef _MAP_H
#define _MAP_H

#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include <vector>
#include "../include/json.hpp"

const int MAX_ENEMY = 75;
const int MAX_BULLETS = 500;
const int MAX_WAVES = 10;          // Nombre max de vagues
const int MAX_TYPES_PER_WAVE = 3;

//pour le json
/**
 * @struct EnemySpawnData
 *
 * @brief Permet de recuperer les infos du JSON pour les utilisee dans le constructeur de Enemy
 */

struct EnemySpawnData {
    char type[32];
    int count;
    int hp;
    int dmg;
    float speed;
    int spriteId;
};

/**
 * @struct Wave
 *
 * @brief contien une vague d ennemies (generer grace au JSON)
 */
struct Wave {
    float triggerTime;
    EnemySpawnData enemyTypes[MAX_TYPES_PER_WAVE];
    int nbTypes; 
    bool triggered;
};



/**
 * @class Map
 *
 * @brief une carte du jeu avec des ennemy et des balles tirer
 *
 */

class Map{
private:
    int idMap;
    Enemy enemies[MAX_ENEMY]; 
    int nbEnemies;
    Bullet bullets[MAX_BULLETS];
    int nbBullets;

    //gestion de waves
    int waveID;
    float timer;
    bool dead;
    int nbWaves;

    Wave waves[MAX_WAVES];

public:
    /**
     * @brief Construteur par defaut de Map
     *
     */
    Map();
    /**
     * @brief Constructeur utilise de Map
     *
     * @param idS L id du sprite utiliser pour la carte
     */
    Map(int idS);
    /**
     * @brief Deplacement des joueur sur la carte
     *
     * @param winWidth largeur de la feunetre
     * @param winHwight hauteur de la feunetre
     * @param players Tableau de joueur a deplacer
     * @param nbPlayers Nombre de joueur a gerer 
     */
    void move(unsigned int winWidth, unsigned int winHeight,Player* players,int nbPlayers);
    /**
     * @brief Permet de faire des degat au ennemy
     */
    int damageE();
    /**
     * @brief Fait des degat a un joueur specifier
     *
     * @param   players joueur a qui faire des degat
     */
     
    void damageP(Player &players);    
    /**
     * @brief Fait des degat a tout le monde (enemy et joueur) garce a damageP et damageE 
     *
     * @param   players tableau de joueur existant
     * @param   nbPlayers nombre de joueur a qui faire des degats
     */
    void damageAll(Player* players,int nbPlayers);
    /**
     * @brief met a jour la carte a chaque tick 
     *
     * @param winWidth largeur de la feunetre
     * @param winHwight hauteur de la feunetre
     * @param players Tableau de joueur a deplacer
     * @param nbPlayers Nombre de joueur a gerer  
     * @param time present pour la gestion des vague (savoir si il faut en mettre une ou pas)
     */
    void update(unsigned  int winWidth, unsigned int winHeight,Player* players,int nbPlayers, float time);
    //utilities to get stuff vacj up to the renderer
    /**
     * @brief renvoie l id de la carte pour l affichage graphique
     *
     * @return l id de la carte 
     */
    int getMapId();
    /**
     * @brief renvoie le nombre d ennemie sur la carte
     *
     * @return le nobre d ennemi
     */
    int getNbEnemies();
        /**
     * @brief renvoie le pointeur vers le premier enemi
     *
     * @return le pointeur vers enemy[0]
     */
    Enemy* getEnemies();

    /**
     * @brief renvoie le nombre de bullet sur la carte
     *
     * @return le nobre de bullet
     */
    int getNbBullet();
    /**
     * @brief renvoie le pointeur vers la premiere bullet
     *
     * @return le pointeur vers bullet[0]
     */
    Bullet* getBullets();

    /**
     * @brief renvoie le temps ecoule
     *
     * @return le temps ecoule
     */
    float getTimer(){return timer;};
    //WAVES
    /**
     * @brief demarre une vague grace au fichier json
     *
     */
    void startWave();  
    /**
     * @brief dit si oui ou non la wave est finie
     *
     * @return l etat de la wave (fini ou non)
     */
    bool isTimeUp() { return (timer >= 150.0f); }
    /**
     * @brief remet a 0 le timer
     *
     */
    void resetTimer() { timer = 0.0f; } 
    /**
     * @brief redemare une carte de 0
     *
     */
    void restart();
    /**
     * @brief permet de charger en memoire une vague d ennemie garce au fichier json
     *
     * @brief le fichier json contenant les waves
     */
    void loadWaves(const char* filename);
    /**
     * @brief remet l etat des wave a 0 
     *
     */
    void resetWaves(); 
    /**
     * @brief dit si oui ou nom toute les vague d ennemie on ete tuer 
     *
     * @param nbEnemies le nombre d ennemie qui devrais etre tuer
     */
    bool allWavesFinished(int nbEnemies) const;

};

#endif