#pragma once

#include <string>
#include "Stats.h"






struct Item {
    char name[20]="N";
    unsigned int price;
    Stats effect;
    bool isSelected;
    int button;
    //On suppose que tous les items ont la meme rareté pour le debut
    int textureID;
};



