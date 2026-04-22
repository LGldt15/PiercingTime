#include "Inventory.h"
#include <iostream>


Weapon::Weapon(unsigned int damage, int t) : baseDamage(damage), type(t) {}

Inventory::Inventory(int round) : nbItems(0), weapon(10, 0) {
    for(int i = 0; i < MAX_ITEMS; i++) {
        items[i].name = "None";
    }
}

void Inventory::addItem(const Item &i) {
    if (nbItems < MAX_ITEMS) {
        items[nbItems] = i; // Copie simple dans la case libre
        nbItems++;
        std::cout << "[Inventory] Item ajoute : " << i.name << " | Bonus : +" << i.effect.attackDamage << " ATK" << std::endl;
    } else {
        std::cout << "[Inventory] Inventaire plein !" << std::endl;
    }
}

int Inventory::getNbItems() const {
    return nbItems;
}

const Item* Inventory::getItems() const {
    return items; 
}

unsigned int Inventory::getTotalDamage() const {
    unsigned int totalBonus = 0;
    for (int i = 0; i < nbItems; i++) {
        totalBonus += items[i].effect.attackDamage;
    }
    return weapon.baseDamage + totalBonus;
}

Weapon& Inventory::getWeapon() {
    return weapon;
}