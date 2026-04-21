#ifndef _INVENTORY_H
#define _INVENTORY_H

#include <vector>
#include "Item.h"

struct Weapon {
    unsigned int baseDamage;
    int type;

    Weapon();
    Weapon(unsigned int damage, int t);
};

class Inventory {
private:
    std::vector<Item> items;
    Weapon weapon;

public:
    Inventory(int round = 0);
    ~Inventory();

    void addItem(Item i);
    
    int getNbItems() const;
    const std::vector<Item>& getItems() const;
    unsigned int getTotalDamage() const;
    Weapon& getWeapon();
};

#endif