#ifndef _SHOP_H
#define _SHOP_H
#include <string>
#include "Structs.h"




class Shop{
private:
Item item[4];//5 different items possible avec chacun un prix et des stats
int currentCursor;

public:
Shop();
~Shop();
void selectValidation(Item &it,Controls& c);
void refreshShop();
Item itemRandSelect();
//getter items
Item getItems();


};






#endif