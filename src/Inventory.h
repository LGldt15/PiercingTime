#ifndef _INVENTORY_H
#define _INVENTORY_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>




struct Item{
    int hpBoost,damageBoost;//eventuelement d autre stat a voir dans el futur
    Item(sf::Texture &t,int damageB=0,int hpB=0);
};

struct Weapon{
    unsigned int baseDamage;
    sf::Sprite* sprite;
    Weapon();
    Weapon(sf::Texture &t,int damage=0);
};

class Inventory{
private:
    std::vector<Item> items;
    Weapon weapon;
public:
    Inventory(int round=0);
    ~Inventory();
    void addItem(Item i);
    void renderInMenu(sf::RenderWindow &window);
};

#endif