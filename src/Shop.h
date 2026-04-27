#ifndef _SHOP_H
#define _SHOP_H
#include <string>
#include "Inventory.h"
#include "Player.h"



/**
 * @class Shop
 *
 * @brief permet de gerer les shop de chaque joueur a la fin de chaque round
 *
 */

class Shop{
private:
Item item[5];//5 different items possible avec chacun un prix et des stats
int currentCursor;

public:
/**
 * @brief Constructeur par defaut de Shop
 *
 */
Shop();
/**
 * @brief Destructeur par defaut de Shop
 *
 */
~Shop();
/**
 * @brief s occupe de regarder quelle item est selectionner garce au controlles et ensuit l ajouter a un joueur specifier
 *
 * @param c controls denner link a un joueur 
 * @param p joueur a qui apretien els inputs 
 */
void handleInput(Controls& c, Player& p);
/**
 * @brief permet de remetre des items dans les cases vide quand on achete un item
 */
void refreshShop();
/**
 * @brief modifie les stat d un joueur avec un item qu il a acheter
 *
 * @param p joueur qui a acheter l item
 * @param i items acheter et donc a "appliquer au joueur"
 */
void effectOnPlayer(Player& p, Item i);
/**
 * @brief renvoie un item aleatoir parmis une liste predefinie
 *
 * @return un item quelconque
 */
Item itemRandSelect();
//getter items
/**
 * @brief renvoie un item specifier 
 *
 * @param index numero de l item a renvoier
 * @return l item spcecifier
 */
Item getItemAt(int index);
/** 
 * @brief renvoie l item actuelement selectioner (pa acheter selectione)
 *
 * @return l id de l item selectionne
 */
int getCurrentCursor();
/** 
 * @brief deplace le curseur de selection vers la gauche
 *
 */
void moveLeft();
/** 
 * @brief deplace le curseur de selection vers la Droite
 *
 */
void moveRight();
/** 
 * @brief version console du shop avant l imlementation graphique
 *
 */
void consoleShop();
};






#endif