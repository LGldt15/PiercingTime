#include "IHM.h"
#include "Bullet.h"
#include "Enemy.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include "../assets/Background.h"
#include "../assets/gromgroi.h"
#include "../assets/player.h"
#include "../assets/caillou.h"

#include <optional>
#include <SFML/Window/Event.hpp> // Pour être sûr d'avoir les définitions d'events
#include <iostream>


IHM::IHM(){
    winWidth=800;
    winHeight=800;
    sf::Vector2<unsigned int> size={winWidth,winHeight};
    window=sf::RenderWindow(sf::VideoMode(size), "My SFML Window");

    mapTypes[0].loadFromMemory(Background_png,Background_png_len);
    mapSprites[0]=new sf::Sprite(mapTypes[0]);

    sf::Vector2f sizeM={800.0f/1200,800.0f/1200};
    mapSprites[0]->setScale(sizeM);

    playerTypes[0].loadFromMemory(player_png,player_png_len);
    playerSprites[0]=new sf::Sprite(playerTypes[0]);

    enemyTypes[0].loadFromMemory(gromgroi_png,gromgroi_png_len);
    enemySprites[0]=new sf::Sprite(enemyTypes[0]);

    bulletTypes[0].loadFromMemory(caillou_png,caillou_png_len);
    bulletSprites[0]=new sf::Sprite(bulletTypes[0]);


    //load font
    if(!font.openFromFile("./assets/font.ttf")) {
        std::cout << "Erreur avec le font" << std::endl;
    }
    
}

void IHM::getInputs(){
    inputs.up=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    inputs.down=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
    inputs.right=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    inputs.left=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    inputs.pause=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
    inputs.select=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
}

IHM::~IHM(){
    for (int i=0;i<2;i++){
        if(playerSprites[i]!=nullptr)delete playerSprites[i];
        
    }
    for (int i=0;i<4;i++){
        if(enemySprites[i]!=nullptr)delete enemySprites[i];
    }
        for (int i=0;i<9;i++){
        if(mapSprites[i]!=nullptr)delete mapSprites[i];
    }
}


void IHM::renderMap(){
    window.clear(sf::Color::Black);
    window.draw(*mapSprites[0]);
    Player* p=game.getPlayers();
    for(int i=0;i<game.getNbJoueur();i++){
        sf::Vector2f pos;
        pos.x=p[i].position.posX;
        pos.y=p[i].position.posY;
        playerSprites[0]->setPosition(pos);
        window.draw(*playerSprites[0]);
    }
    Enemy* enemyzero=game.getEnemies();
    for(int i=0;i<50;i++){
        if(enemyzero[i].isAlive){
            sf::Vector2u s=enemyTypes[enemyzero[i].sprite].getSize();
            sf::Vector2f si={100.0f/s.x,60.0f/s.y};
            //std::cout<<"here and si is :"<<si.x<<' '<<si.y<<std::endl;
            enemySprites[0]->setScale(si);
            sf::Vector2f pos;
            pos.x=enemyzero[i].position.posX;
            pos.y=enemyzero[i].position.posY;
            enemySprites[0]->setPosition(pos);
            window.draw(*enemySprites[0]);
        }
    }
    Bullet* bulletzero=game.getBullets();
    for(int i=0;i<game.getNbBullets();i++){
        if (bulletzero[i].damage!=0){
            sf::Vector2f pos;
            pos.x=bulletzero[i].pos.posX;
            pos.y=bulletzero[i].pos.posY;
            bulletSprites[bulletzero[i].getSprite()]->setPosition(pos);
            window.draw(*bulletSprites[0]);
        }
    }
    window.display(); 
}

void IHM::gameLoop(){
    while (window.isOpen()){
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>() )
                  window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
                window.close();
            //remplacer par le menu de pause
        }
            

        getInputs();
        game.update(inputs, winWidth, winHeight);
        renderMap();
    }
}

void IHM::renderMenu() {

}

void IHM::playerSelect() {

}


void IHM::handleShopInput() { //tq le joueur 1 joue avec fleche et entree et le 2 joue avec zqsd et espace
    std::optional<sf::Event> event;
    
    while (event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) window.close();

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            
            // JOUEUR 1 
            bool L1 = (keyPressed->code == sf::Keyboard::Key::Left);
            bool R1 = (keyPressed->code == sf::Keyboard::Key::Right);
            bool S1 = (keyPressed->code == sf::Keyboard::Key::Enter);
            game.getShop(0).selectValidation(L1, R1, S1, game.getPlayers()[0]);

            // JOUEUR 2 
            if (game.getNbJoueur() > 1) {
                bool L2 = (keyPressed->code == sf::Keyboard::Key::Q);
                bool R2 = (keyPressed->code == sf::Keyboard::Key::D);
                bool S2 = (keyPressed->code == sf::Keyboard::Key::Space);
                game.getShop(1).selectValidation(L2, R2, S2, game.getPlayers()[1]);
            }

            // Touche pour quitter le shop E
            if (keyPressed->code == sf::Keyboard::Key::E) {
                game.setShopActive(false); 
            }
        }
    }
}

void IHM::renderShop() {
    window.clear(sf::Color(20, 20, 30)); 

    for (int pIdx = 0; pIdx < game.getNbJoueur(); pIdx++) {
        Shop& currentShop = game.getShop(pIdx);
        Player& currentPlayer = game.getPlayers()[pIdx];

        // On définit un décalage vertical pour chaque joueur
        float offsetY = pIdx * 350.f; 

        // Affichage Gold du Joueur P
        sf::Text goldText(font);
        goldText.setString("P" + std::to_string(pIdx+1) + " Gold: " + std::to_string(currentPlayer.getGold()));
        goldText.setPosition({50.f, 50.f + offsetY});
        window.draw(goldText);

        // Boucle sur les items du shop du joueur P
        for (int i = 0; i < 4; i++) {
            Item item = currentShop.getItemAt(i);
            sf::Vector2f pos = {100.f + i * 170.f, 120.f + offsetY};

            sf::RectangleShape box({150.f, 200.f});
            box.setPosition(pos);
            
            // Curseur spécifique à ce joueur
            if (currentShop.getCurrentCursor() == i) {
                box.setOutlineColor(sf::Color::Yellow);
                box.setOutlineThickness(4.f);
            } else {
                box.setOutlineColor(sf::Color::White);
            }
            
            box.setFillColor(sf::Color(40, 40, 60));
            window.draw(box);

            // ... Dessiner le nom et prix de l'item ici ...
        }
    }
    window.display();
}