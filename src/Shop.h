#ifndef _SHOP_H
#define _SHOP_H
#include <string>
#include "Inventory.h"
#include "Player.h"




class Shop{
private:
Item item[5];//5 different items possible avec chacun un prix et des stats
int currentCursor;

public:
Shop();
~Shop();
void selectValidation(Controls& c,Player& p );
void refreshShop();
void effectOnPlayer(Player& p, Item i);
Item itemRandSelect();
//getter items
Item getItems();


};






#endif