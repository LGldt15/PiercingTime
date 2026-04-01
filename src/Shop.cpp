#include "Shop.h"
#include<iostream>

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
            selectedItem.effect.hp=-10;

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

//EVENTUELLEMENT UTILISER UNE MAP POUR REMPLIR
//ajouter le nom du fichier de l image de chacun csv
}


void Shop::refreshShop() {
    for (int i = 0; i < 4; i++) {
        if (item[i].name == "None") {
            item[i] = itemRandSelect(); 
            item[i].button = i + 1;     
            item[i].isSelected = false;
        }
     
    }
    
}


Item Shop::getItems(){
    return item[3];
}




// Shop.cpp
void Shop::selectValidation(bool moveLeft, bool moveRight, bool attemptSelect, Player& p) {
    
    if (moveRight && currentCursor < 3) {
        currentCursor++;
    }
    if (moveLeft && currentCursor > 0) {
        currentCursor--;
    }

    if (attemptSelect) {
        Item& target = item[currentCursor];
        
        if (target.name != "None" && p.getGold() >= target.price) {
            effectOnPlayer(p, target);
            target.name = "None";
            target.price = 0;
            target.isSelected = true; 
        }
    }
}



//modification des stats de player dont le gold
void Shop::effectOnPlayer(Player &p, Item i) {

    Stats& s = p.getStats();


    int newGold = p.getGold() - i.price; //pr pas modifier une copie
    p.setGold(newGold);


    s.attackDamage+= i.effect.attackDamage;
    s.playerSpeed+= i.effect.playerSpeed;
    s.bulletSpeed+= i.effect.bulletSpeed;
    s.hp+= i.effect.hp;


}


/*                 SHOP VERSION TEXTE                                             */
Item Shop::getItemAt(int index){
if (index >= 0 && index < 4) return item[index];
return Item();
}


int  Shop::getCurrentCursor(){return currentCursor;}

void Shop::moveLeft(){if(currentCursor<4 && currentCursor>=0)currentCursor-=1;}
void Shop::moveRight(){if(currentCursor!=0)currentCursor+=1;}

