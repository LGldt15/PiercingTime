#include "Shop.h"
#include<iostream>
#include <random>
#include <time.h>

Shop::Shop(){
//init des prix
    for (int i=0; i<4; i++){
        item[i].price=0;
        item[i].name="None";
        item[i].button=0;
        item[i].isSelected=false;
    }
    std::cout<<"shop initialisé"<<std::endl;

}

Shop::~Shop(){
//auto
}

Item Shop::itemRandSelect(){
    Item selectedItem
    int randInt = (rand() % 5) + 1; 
    switch(randInt)
    {
        case 1:

            selectedItem.name="Dino essence";
            selectedItem.price=40;
            selectedItem.effect.attackDamage=10.0f;
            selectedItem.effect.attackSpeed=0.5f;
            selectedItem.effect.PlayerSpeed=0.5f;
            selectedItem.effect.hpBoost=20.0f;
            break;
        case 2:

            selectedItem.name="Rubber Elastic";
            selectedItem.price=10;
            selectedItem.effect.attackDamage=0;
            selectedItem.effect.attackSpeed=1.5f;
            selectedItem.effect.PlayerSpeed=0;
            selectedItem.effect.hpBoost=0;
            break;
        case 3:

            selectedItem.name="Armadillo Shell";
            selectedItem.price=35;
            selectedItem.effect.attackDamage=10.0f;
            selectedItem.effect.attackSpeed=-0.5;
            selectedItem.effect.PlayerSpeed=-0.5f;
            selectedItem.effect.hpBoost=50.0f;
            break;
        case 4:

            selectedItem.name="Weird Black Liquid";//petrol
            selectedItem.price=75;
            selectedItem.effect.attackDamage=20.0f;
            selectedItem.effect.attackSpeed=8.0f;
            selectedItem.effect.PlayerSpeed=2.5f;
            selectedItem.effect.hpBoost=-10.0f;

            break;
        case 5:

            selectedItem.name="Bone Broth";
            selectedItem.price=15;
            selectedItem.effect.attackDamage=5.0f;
            selectedItem.effect.attackSpeed=2.0f;
            selectedItem.effect.PlayerSpeed=0.5f;
            selectedItem.effect.hpBoost=25.0f;

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
            item[i].button=i+1;


        }
        else{
            item[i]=itemRandSelect();
            item[i].button=i;

        }
        
    itemToDisplay--;
    }
    



}

}



Item Shop::getItems(){
    return item[5];

}



void Shop::selectValidation(Controls& c){


}