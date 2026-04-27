#pragma once
#define MAX_ITEMS 10

#include "Item.h"


/**
 * @struct Weapon
 *
 * @brief structure qui definie une arme (les degat et son sprite)
 *
 */

struct Weapon {
    unsigned int baseDamage;
    int type;

    /**
     *
     * @brief Constructeur de Weapon pour lui assigner des vleur a la construction
     *
     * @param damage les degat de l arme
     * @param t l id de la texture 
     */
    Weapon(unsigned int damage, int t);
};

/**
 * @class Inventory
 *
 * @brief Decrit un inventaire d un joueur (ses armes et ses items)
 *
 */

class Inventory {
private:
    Item items[MAX_ITEMS]; 
    int nbItems;  
    Weapon weapon;        

public:
    /**
     * @brief Constructeur par defaut de Inventaire
     *
     */
    Inventory();
    
    /**
     * @brief Ajoute un Item a l inventaire
     *
     * @param i item a rajouter a l inventaire du joueur
     */
    void addItem(const Item &i);
    /**
    * @brief renvoie le nombre d item d un joueur
    *
    * @return le nombre d item dans l inventaire
    */
    int getNbItems() const;
    /**
    * @brief renvoie le pointeur vers le Item[0] et permet d onc avec getnbItem de parcourire les tableau a partire de l IHM
    *
    * @return l inventaire
    */
    const Item* getItems() const; 
    /**
    * @brief renvoie les degat total du joueur 
    *
    * @return la quantite de degat
    */
    unsigned int getTotalDamage() const;
    /**
    * @brief renvoie l'arme du joueur
    *
    * @return l'arme du joueur
    */
    Weapon& getWeapon();
};