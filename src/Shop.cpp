#include "Shop.h"
#include<iostream>
#include <random>
#include <time.h>

Shop::Shop(){
//init des prix
    currentCursor=0; //selector dans le shop ≠ boutton d item
    for (int i=0; i<4; i++){
        item[i].price=0;
        item[i].name="None";
        item[i].button=0;
        item[i].isSelected=false;
        //on touchera pas au gold, a l exp ou autres
    }
    std::cout<<"shop initialisé"<<std::endl;

}

Shop::~Shop(){
//auto
}

Item Shop::itemRandSelect(){
    Item selectedItem;
    int randInt = (rand() % 5) + 1; 
    switch(randInt)
    {
        case 1:

            selectedItem.name="Dino essence";
            selectedItem.price=40;
            selectedItem.effect.attackDamage=10.0f;
            selectedItem.effect.bulletSpeed=0.5f;
            selectedItem.effect.playerSpeed=0.5f;
            selectedItem.effect.hp=20.0f;
        
            break;
        case 2:

            selectedItem.name="Rubber Elastic";
            selectedItem.price=10;
            selectedItem.effect.attackDamage=0;
            selectedItem.effect.bulletSpeed=1.5f;
            selectedItem.effect.playerSpeed=0;
            selectedItem.effect.hp=0;
            break;
        case 3:

            selectedItem.name="Armadillo Shell";
            selectedItem.price=35;
            selectedItem.effect.attackDamage=10.0f;
            selectedItem.effect.bulletSpeed=-0.5;
            selectedItem.effect.playerSpeed=-0.5f;
            selectedItem.effect.hp=50.0f;
            break;
        case 4:

            selectedItem.name="Weird Black Liquid";//petrol
            selectedItem.price=75;
            selectedItem.effect.attackDamage=20.0f;
            selectedItem.effect.bulletSpeed=8.0f;
            selectedItem.effect.playerSpeed=2.5f;
            selectedItem.effect.hp=-10.0f;

            break;
        case 5:

            selectedItem.name="Bone Broth";
            selectedItem.price=15;
            selectedItem.effect.attackDamage=5.0f;
            selectedItem.effect.bulletSpeed=2.0f;
            selectedItem.effect.playerSpeed=0.5f;
            selectedItem.effect.hp=25.0f;

            break;
        default:
            break;
    }
  return (selectedItem);


}


void Shop::refreshShop(){
//srand(Time(null)) 
// random des items

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



void Shop::selectValidation(Controls& c, Player& p) {

    if (c.right && currentCursor < 3) currentCursor++;
    if (c.left && currentCursor > 0) currentCursor--;

    if (c.select) {
        Item& target = item[currentCursor];

        if (target.name != "None" && p.gold >= target.price) {
            

            //ici mettre fonction qui applique les effets de l item et eneleve les gold au joueur

            // On vide le slot du shop
            target.name = "None";
            target.price = 0;
        }
    }
}



//ICI METTRE LA FONCTION QUAND JAURAI RECUP LES TRUCS A CHARLIE