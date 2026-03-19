#ifndef _SHOP_H
#define _SHOP_H
<<<<<<< HEAD
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










=======

class Shop{

};

>>>>>>> 49d8d7c4d7c0de7889ead7bac7e3d482bfd7522e
#endif