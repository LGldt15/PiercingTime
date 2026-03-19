#include "Shop.h"
#include<iostream>
#include <random>
#include <time.h>

Shop::Shop(){
//init des prix
    for (int i=0; i<5; i++){
        item[i].price=0;
        item[i].name="None";
        item[i].isSelected=false;
    }
    std::cout<<"shop initialisé"<<std::endl;

}

Shop::~Shop(){
//auto
}

Item Shop::itemRandSelect(){

    int randInt= rand()%5;
    Item SelectedItem;

    switch(randInt)
    {
        case 1:

            SelectedItem.name="Dino essence";
            SelectedItem.price=40;
            SelectedItem.effect.attackDamage=10.0f;
            SelectedItem.effect.attackSpeed=0.5f;
            SelectedItem.effect.PlayerSpeed=0.5f;
            SelectedItem.effect.hpBoost=20.0f;
            break;
        case 2:

            SelectedItem.name="Rubber Elastic";
            SelectedItem.price=10;
            SelectedItem.effect.attackDamage=0;
            SelectedItem.effect.attackSpeed=1.5f;
            SelectedItem.effect.PlayerSpeed=0;
            SelectedItem.effect.hpBoost=0;
            break;
        case 3:

            SelectedItem.name="Armadillo Shell";
            SelectedItem.price=35;
            SelectedItem.effect.attackDamage=10.0f;
            SelectedItem.effect.attackSpeed=-0.5;
            SelectedItem.effect.PlayerSpeed=-0.5f;
            SelectedItem.effect.hpBoost=50.0f;
            break;
        case 4:

            SelectedItem.name="Weird Black Liquid";//petrol
            SelectedItem.price=75;
            SelectedItem.effect.attackDamage=20.0f;
            SelectedItem.effect.attackSpeed=8.0f;
            SelectedItem.effect.PlayerSpeed=2.5f;
            SelectedItem.effect.hpBoost=-10.0f;

            break;
        case 5:

            SelectedItem.name="Bone Broth";
            SelectedItem.price=15;
            SelectedItem.effect.attackDamage=5.0f;
            SelectedItem.effect.attackSpeed=2.0f;
            SelectedItem.effect.PlayerSpeed=0.5f;
            SelectedItem.effect.hpBoost=25.0f;

            break;
        default:
            break;
    }
  return (SelectedItem);





}





void Shop::refreshShop(){
//srand(Time(null)) 
// randomisation des items

int itemToDisplay=4;

while(itemToDisplay!=0){

    for (int i = 0; i < 4; i++)
    {
        if (item[i].isSelected){
            item[i].isSelected=false;
            item[i]=itemRandSelect();

        }
        

    }
    


itemToDisplay--;
}

}



Item Shop::getItems(){
    return item[5];

}
