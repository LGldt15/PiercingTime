#include "Shop.h"
#include<iostream>
#include <random>
#include <time.h>

Shop::Shop(){
//init des prix
    for (int i=0; i<5; i++){
        item[i].price=0;
        item[i].name="None";
    }
    std::cout<<"shop initialisé"<<std::endl;

}

Shop::~Shop(){
//auto
}

void Shop::itemInit(){
    //item 1
    Item dinoEssence;
    dinoEssence.name="Dino essence";
    dinoEssence.price=40;
    dinoEssence.effect.attackDamage=10.0f;
    dinoEssence.effect.attackSpeed=0.5f;
    dinoEssence.effect.PlayerSpeed=0.5f;
    dinoEssence.effect.hpBoost=20.0f;

    //item 2
    Item rubberElastic;
    rubberElastic.name="Rubber Elastic";
    rubberElastic.price=10;
    rubberElastic.effect.attackDamage=0;
    rubberElastic.effect.attackSpeed=1.5f;
    rubberElastic.effect.PlayerSpeed=0;
    rubberElastic.effect.hpBoost=0;

    //item 3
    Item armadilloShell;
    armadilloShell.name="Armadillo Shell";
    armadilloShell.price=35;
    armadilloShell.effect.attackDamage=10.0f;
    armadilloShell.effect.attackSpeed=-0.5;
    armadilloShell.effect.PlayerSpeed=-0.5f;
    armadilloShell.effect.hpBoost=50.0f;

    //item 
    Item weirdBlackLiquid;
    weirdBlackLiquid.name="Weird Black Liquid";//petrol
    weirdBlackLiquid.price=75;
    weirdBlackLiquid.effect.attackDamage=20.0f;
    weirdBlackLiquid.effect.attackSpeed=8.0f;
    weirdBlackLiquid.effect.PlayerSpeed=2.5f;
    weirdBlackLiquid.effect.hpBoost=-10.0f;


    //item
    Item boneBroth;
    boneBroth.name="Bone Broth";
    boneBroth.price=15;
    boneBroth.effect.attackDamage=5.0f;
    boneBroth.effect.attackSpeed=2.0f;
    boneBroth.effect.PlayerSpeed=0.5f;
    boneBroth.effect.hpBoost=25.0f;





}




void Shop::refreshShop(){
//srand(Time(null)) 
// randomisation des items

int itemToDisplay=0;

while(itemToDisplay!=0){

    for (int i = 0; i < 4; i++)
    {
        if (){


        }
        

    }
    



}

}



Item Shop::getItems(){
    return item[5];

}
