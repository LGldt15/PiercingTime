

struct Stats{
float PlayerSpeed, attackDamage, attackSpeed, hpBoost;
};

struct Item {
    std::string name;
    int price;
    Stats effect;

    //On suppose que tous les items ont la meme rareté pour le debut

};



struct Controls{
    bool up;
    bool down;
    bool right;
    bool left;
    bool pause;
    bool select;
};

