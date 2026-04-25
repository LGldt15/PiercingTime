#include "Shop.h"
#include <iostream>
#include <assert.h>
#include <cstring> 

Shop::Shop() {
    currentCursor = 0;
    for (int i = 0; i < 4; i++) {
        item[i].price = 0;

        std::strncpy(item[i].name, "None", 31);
        item[i].name[31] = '\0';
        item[i].button = 0;
        item[i].isSelected = false;
    }
    std::cout << "Shop initialisé" << std::endl;
}

Shop::~Shop() {}

Item Shop::itemRandSelect() {
    Item selectedItem = {};
    int randInt = (rand() % 5) + 1;
    
    // Initialisation par défaut
    selectedItem.effect.attackDamage = 0;
    selectedItem.effect.bulletSpeed = 0;
    selectedItem.effect.playerSpeed = 0;
    selectedItem.effect.hp = 0;

    switch (randInt) {
        case 1:
            std::strncpy(selectedItem.name, "Dino essence", 31);
            selectedItem.price = 40;
            selectedItem.effect.attackDamage = 10;
            selectedItem.effect.bulletSpeed = 0.5f;
            selectedItem.effect.playerSpeed = 0.5f;
            selectedItem.effect.hp = 20.0f;
            break;
        case 2:
            std::strncpy(selectedItem.name, "Rubber Elastic", 31);
            selectedItem.price = 10;
            selectedItem.effect.bulletSpeed = 1.5f;
            break;
        case 3:
            std::strncpy(selectedItem.name, "Armadillo Shell", 31);
            selectedItem.price = 35;
            selectedItem.effect.attackDamage = 10.0;
            selectedItem.effect.bulletSpeed = -0.5;
            selectedItem.effect.playerSpeed = -0.5f;
            selectedItem.effect.hp = 50.0f;
            break;
        case 4:
            std::strncpy(selectedItem.name, "Weird Black Liquid", 31);
            selectedItem.price = 75;
            selectedItem.effect.attackDamage = 20;
            selectedItem.effect.bulletSpeed = 8.0;
            selectedItem.effect.playerSpeed = 2.5;
            selectedItem.effect.hp = -10;
            break;
        case 5:
            std::strncpy(selectedItem.name, "Bone Broth", 31);
            selectedItem.price = 15;
            selectedItem.effect.attackDamage = 5;
            selectedItem.effect.bulletSpeed = 2.0f;
            selectedItem.effect.playerSpeed = 0.5f;
            selectedItem.effect.hp = 25.0f;
            break;
    }
    selectedItem.name[31] = '\0'; // Sécurité
    return selectedItem;
}

void Shop::refreshShop() {
    for (int i = 0; i < 4; i++) {
        // Utilisation de strcmp pour comparer les char[]
        if (std::strcmp(item[i].name, "None") == 0) {
            item[i] = itemRandSelect();
            item[i].button = i + 1;
            item[i].isSelected = false;
        }
    }
}

void Shop::handleInput(Controls& c, Player& p) {
    if (c.right && currentCursor < 3) currentCursor++;
    if (c.left && currentCursor > 0) currentCursor--;

    if (c.select) {
        assert(currentCursor >= 0 && currentCursor < 4);
        Item& target = item[currentCursor];

        // Comparaison avec strcmp
        if (std::strcmp(target.name, "None") != 0) {
            if (p.getGold() >= target.price) {
                p.setGold(p.getGold() - target.price);
                p.getInventory().addItem(target);
                effectOnPlayer(p, target);

                // On réinitialise l'item acheté
                Item newItem = itemRandSelect();
                target = newItem;
                target.button = currentCursor + 1;
                target.isSelected = false;
            } else {
                std::cout << "[SHOP] Pas assez d'or" << std::endl;
            }
        }
    }
}

void Shop::effectOnPlayer(Player &p, Item i) {
    Stats& s = p.getStats();
    s.playerSpeed += i.effect.playerSpeed;
    s.bulletSpeed += i.effect.bulletSpeed;
    s.hp += i.effect.hp;
}

Item Shop::getItemAt(int index) {
    if (index >= 0 && index < 4) return item[index];
    return Item(); // Retourne un item vide si index invalide
}

int Shop::getCurrentCursor() { return currentCursor; }

void Shop::moveLeft() { if(currentCursor > 0) currentCursor--; }
void Shop::moveRight() { if(currentCursor < 3) currentCursor++; }