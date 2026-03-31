#include <string>

//SVP ESSAYER DE NE PAS CHANGER LES STRUCTURES SANS PREVENIR! MERCI :)

struct Stats{
float playerSpeed, bulletSpeed;
unsigned int attackDamage, hp;
};

struct Item {
    std::string name;
    unsigned int price;
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
    // id pour chacun
    //faire une class evenement utilisable partt
};

