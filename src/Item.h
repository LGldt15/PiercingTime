#pragma once

#include <string>
#include "Stats.h"





/**
 * @struct Item
 *
 * @brief Item utiliser dasn le shop ( a donc des starts qu il deva ajouter a un jouer quand il est acheter)
 *
 */

struct Item {
    char name[30]="N";
    unsigned int price;
    Stats effect;
    bool isSelected;
    int button;
    //On suppose que tous les items ont la meme rareté pour le debut
    int textureID;
};



