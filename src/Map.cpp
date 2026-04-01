#include "Map.h"
#include "Bullet.h"
#include "Player.h"
  
#include <iostream>
  //int idMap;
  //  Player* players;
  //  int nbPlayers;
  //  Enemy* enemies;
  //  int nbEnemies;
  //  Bullet* bullets;
  //  int nbBullets;
    
Map::Map(){

    idMap=0;
    nbPlayers=0;
    nbEnemies=0;
    nbBullets=0;
}


Map::Map(int idS,Player &p,int nbP){
    idMap=idS;
    players[0]=&p;
    nbPlayers=nbP;
    nbEnemies=2;
    enemies[0]=Enemy(1,0,true,0.05,0);
    enemies[1]=Enemy(1,0,true,0.05,0);
    nbBullets=0;
    for (int i=0;i<499;i++){
        bullets[i].next=&bullets[i+1];
    }
}


void Map::move(Controls &c,unsigned int winWidth, unsigned int winHeight){
    for (int i=0;i<nbPlayers;i++){
        players[i]->move(c,winWidth, winHeight);


        for (int j=0;j<nbEnemies;j++){
            enemies[j].move(players[i]->position);

        }
    }    
    for (int i=0;i<nbBullets;i++){
        bullets[i].move();
    }

}


    
void Map::damageE(){
    for(int i=0;i<50;i++){
        if(enemies[i].isAlive){
            for(int j=0;j<500;j++){
                if (bullets[j].damage!=0) {
                    enemies[i].takeDamageBullet(bullets[j]);
                }
            }
        }
    }
}

void Map::damageP(int player){
    int iter=nbEnemies;
    for(int i=0;i<iter;i++){
        if(enemies[i].isAlive){
            if(players[player]->takeDamage(enemies[i])) return;
        }
        else iter++;
    }
    iter=nbBullets;
    for(int i=0;i<iter;i++){
        if(bullets[i].damage!=0){
            if(players[player]->takeDamageBullet(bullets[i])){
                bullets[i].next=bullets[0].next;
                bullets[0].next=&bullets[i];
                return;
            } 
        }
        else iter++;
    }
}

void Map::damageAll(){

    for(int i=0;i<nbPlayers;i++){
        damageP(i);
    }

    damageE();
}

void Map::update(Controls& c, unsigned  int winWidth, unsigned int winHeight){
    move(c, winWidth, winHeight);
    damageAll();
    for(int i=0;i<nbPlayers;i++){
        if(bullets[0].damage==0 && players[i]->cooldown<=0){

            players[i]->shoot(bullets[0], nbEnemies, enemies);
            nbBullets++;
            players[i]->cooldown=1000;

        }
        else if (nbBullets<500 && players[i]->cooldown<=0 && bullets[0].next!=nullptr){

            int k=0;
            for(int j=0;j<500;j++){
                if (bullets[k].pos.posX<0 || bullets[k].pos.posX>800 || bullets[k].pos.posY<0 || bullets[k].pos.posY>800){
                    bullets[k].damage=0;
                    bullets[k].pos={0,0};
                    bullets[k].speed={0,0};
                    k--;
                    nbBullets--;
                }
                if (bullets[k].damage!=0){
                    k++;
                }
            }
            players[i]->shoot(bullets[k], nbEnemies, enemies);
            nbBullets++;
            players[i]->cooldown=1000;
            for (int i=0;i<nbBullets;i++){

            }
        }
    }

       // updateShop(shop, *players[0]);


}


int Map::getMapId(){
    return idMap;
}
int Map::getNbEnemies(){
    return nbEnemies;
}
Enemy* Map::getEnemies(){
    return &enemies[0];
}


int Map::getNbBullet(){
    return nbBullets;
}
Bullet* Map::getBullets(){
    return &bullets[0];
}


  /*void Map::updateShop(Shop& shop, Player& player) {
    bool inShop = true;
    shop.refreshShop(); // On remplit le shop avec de nouveaux items

    while (inShop) {
        std::cout << "\n=== BIENVENUE AU SHOP (Fin de Niveau) ===" << std::endl;
        std::cout << "Votre Or : " << player.getGold() << " GP" << std::endl;
        std::cout << "------------------------------------------" << std::endl;

        for (int i = 0; i < 4; i++) {
            Item current = shop.getItemAt(i); // Utilise une fonction getter (voir plus bas)
            std::cout << i + 1 << ". ";
            if (current.name == "None") {
                std::cout << "[VENDU]";
            } else {
                std::cout << current.name << " - Prix : " << current.price << " GP";
            }
            if (i == shop.getCurrentCursor()) std::cout << " <---"; // Curseur visuel
            std::cout << std::endl;
        }

        std::cout << "------------------------------------------" << std::endl;
        std::cout << " Gauche |  Droite | Acheter | quitter" << std::endl;

        char input;
        std::cin >> input;
        input = toupper(input);

        Controls c = {false}; 
        if (input == 'l') { shop.moveLeft(); } 
        if (input == 'r') { shop.moveRight(); }
        if (input == 'e') {
            c.select = true;
            shop.selectValidation(c, player);
        }
        if (input == 'q') {
            inShop = false;
        }
    }
    std::cout << "NEXT lvl" << std::endl;
}
*/