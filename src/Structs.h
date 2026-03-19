#include <string>

struct Stats{
float PlayerSpeed, attackDamage, attackSpeed, hpBoost;
};

struct Item {
    std::string name;
    int price;
    Stats effect;
    bool isSelected;
    int button;
    //On suppose que tous les items ont la meme rareté pour le debut

};

struct Controls{
    bool up;//1
    bool down;//2
    bool right;//3
    bool left;//4
    bool pause;//5
    bool select;//6
};

