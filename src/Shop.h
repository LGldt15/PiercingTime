#ifndef _SHOP_H
#define _SHOP_H
#include "Stats.h"

struct Item {
    std::string name;
    int price;
    Stats effect;
    //On suppose que tous les items ont la meme rareté pour le debut

};

class Shop{
private:
Stats items[5]; //5 different items possible 


public:
Shop();
~Shop();
void refreshShop();


};










#endif