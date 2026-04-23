#pragma once
#define MAX_ITEMS 10

#include "Item.h"

struct Weapon {
    unsigned int baseDamage;
    int type;


    Weapon(unsigned int damage, int t);
};


class Inventory {
private:
    Item items[MAX_ITEMS]; 
    int nbItems;  
    Weapon weapon;        

public:
    Inventory(int round = 0);
    
    
    void addItem(const Item &i);
    int getNbItems() const;
    const Item* getItems() const; 
    unsigned int getTotalDamage() const;
    Weapon& getWeapon();
};