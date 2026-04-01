#include <string>
#include "Stats.h"

struct Item {
    std::string name;
    unsigned int price;
    Stats effect;
    bool isSelected;
    int button;
    //On suppose que tous les items ont la meme rareté pour le debut

};