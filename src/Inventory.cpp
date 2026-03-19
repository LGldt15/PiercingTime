#include "Inventory.h"
#include <SFML/Graphics/Texture.hpp>



Weapon::Weapon(){
    baseDamage=0;
}

Weapon::Weapon(sf::Texture &t,int damage) {
    baseDamage=damage;
    sprite->setTexture(t);
}



Inventory::Inventory(int round){
    switch (round){//modification de la rme en fonction du round
        case 0:{
             weapon=Weapon();//a renomer quand on aura les sprite
             break;
        }
    }
}

Inventory::~Inventory(){
    items.clear();
}

void Inventory::addItem(Item i){
    items.push_back(i);
}

