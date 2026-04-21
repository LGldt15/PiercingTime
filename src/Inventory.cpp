#include "Inventory.h"
#include <iostream>

Weapon::Weapon() : baseDamage(10), type(0) {}

Weapon::Weapon(unsigned int damage, int t) : baseDamage(damage), type(t) {}

Inventory::Inventory(int round) {
    items.clear();
    weapon = Weapon(10, 0); 
}

Inventory::~Inventory() {
    items.clear();
}

void Inventory::addItem(Item i) {
    items.push_back(i);
    std::cout << "[Inventory] Item ajoute : " << i.name << " | Bonus : +" << i.effect.attackDamage << " ATK" << std::endl;
}

int Inventory::getNbItems() const {
    return static_cast<int>(items.size());
}

const std::vector<Item>& Inventory::getItems() const {
    return items;
}

unsigned int Inventory::getTotalDamage() const {
    unsigned int totalBonus = 0;
    for (const auto& item : items) {
        totalBonus += item.effect.attackDamage;
    }
    return weapon.baseDamage + totalBonus;
}

Weapon& Inventory::getWeapon() {
    return weapon;
}