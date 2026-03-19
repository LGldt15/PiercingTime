#ifndef _SHOP_H
#define _SHOP_H
#include <string>
#include "Stats.h"



class Shop{
private:
Stats items[5]; //5 different items possible 


public:
Shop();
~Shop();
void refreshShop();



};







#endif