#include "Shop.h"
#include<iostream>
#include<assert.h>

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
    Item selectedItem= {};
    int randInt = (rand() % 5) + 1; 
    switch(randInt)
    {
        case 1:

            selectedItem.name="Dino essence";
            selectedItem.price=40;
            selectedItem.effect.attackDamage=10;
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
            selectedItem.effect.attackDamage=10.0;
            selectedItem.effect.bulletSpeed=-0.5;
            selectedItem.effect.playerSpeed=-0.5f;
            selectedItem.effect.hp=50.0f;
            break;
        case 4:

            selectedItem.name="Weird Black Liquid";//petrol
            selectedItem.price=75;
            selectedItem.effect.attackDamage=20;
            selectedItem.effect.bulletSpeed=8.0;
            selectedItem.effect.playerSpeed=2.5;
            selectedItem.effect.hp=-10;

            break;
        case 5:

            selectedItem.name="Bone Broth";
            selectedItem.price=15;
            selectedItem.effect.attackDamage=5;
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
        // On ne remplace que les items achetés ou vides
        if (item[i].name == "None") {
            item[i] = itemRandSelect();
            item[i].button = i + 1;
            item[i].isSelected = false;
        }
    }
}

void Shop::handleInput(Controls& c, Player& p) {
    // 1. NAVIGATION : Déplacement du curseur
    // On vérifie les bornes pour ne pas sortir du tableau
   

    if (c.right && currentCursor < 3) {
        currentCursor++;
    }
    if (c.left && currentCursor > 0) {
        currentCursor--;
    }


    if (c.select) {
    assert(currentCursor >= 0 && currentCursor < 4);
        Item& target = item[currentCursor]; 
        

        if (target.name != "None") {
            if (p.getGold() >= target.price) {
                

                p.setGold(p.getGold() - target.price);
                

                p.getInventory().addItem(target); 
                effectOnPlayer(p, target);     
                
              //std::cout << "[SHOP] bought: " << target.name << std::endl;
                std::cout<<"new player dmg :"<< p.getInventory().getTotalDamage()<<std::endl;

                target = itemRandSelect(); 
                target.button = currentCursor + 1; 
                target.isSelected = false;
                
            } else {
                std::cout << "[SHOP]not enough gold" << std::endl;
            }
        }
    }
}


void Shop::effectOnPlayer(Player &p, Item i) {
    Stats& s = p.getStats();

 
    s.playerSpeed += i.effect.playerSpeed;
    s.bulletSpeed += i.effect.bulletSpeed;
    s.hp += i.effect.hp;
}


/*                 SHOP VERSION TEXTE                                             */
Item Shop::getItemAt(int index){
if (index >= 0 && index < 4) return item[index];
return Item();
}


int  Shop::getCurrentCursor(){return currentCursor;}

void Shop::moveLeft(){if(currentCursor<4 && currentCursor>=0)currentCursor-=1;}
void Shop::moveRight(){if(currentCursor!=0)currentCursor+=1;}

