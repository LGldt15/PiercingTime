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
    window=sf::RenderWindow(sf::VideoMode(size), "Piercing Time");

    mapTypes[0].loadFromMemory(Background_png,Background_png_len);
    for(int i=0; i<9; i++) mapSprites[i] = nullptr;
    mapSprites[0]=new sf::Sprite(mapTypes[0]);

    sf::Vector2f sizeM={800.0f/1200,800.0f/1200};
    mapSprites[0]->setScale(sizeM);

    playerTypes[0].loadFromMemory(player_png,player_png_len);
    for(int i=0; i<2; i++) playerSprites[i] = nullptr;
    playerSprites[0]=new sf::Sprite(playerTypes[0]);

    enemyTypes[0].loadFromMemory(gromgroi_png,gromgroi_png_len);
    for(int i=0; i<4; i++) enemySprites[i] = nullptr;
    enemySprites[0]=new sf::Sprite(enemyTypes[0]);

    bulletTypes[0].loadFromMemory(caillou_png,caillou_png_len);
    for(int i=0; i<9; i++) bulletSprites[i] = nullptr;
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();
        // Process events
        if (game.isInShop()) {
            handleShopInput(); 
            renderShop();      
        }else{
        while (const std::optional event = window.pollEvent())
        {

            if (event->is<sf::Event::Closed>() )
                  window.close();
            
        
            //remplacer par le menu de pause
        }
            

        getInputs();
        game.update(inputs, winWidth, winHeight);
        renderMap();
    }}
}

void IHM::renderMenu() {

}

void IHM::playerSelect() {

}


//PARTIE shop

void IHM::handleShopInput() {

    while (const std::optional event = window.pollEvent()) {
        

        if (event->is<sf::Event::Closed>()) {
            window.close();
        }


        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            

            Controls shopControls;
            shopControls.left   = (keyPressed->code == sf::Keyboard::Key::Left);
            shopControls.right  = (keyPressed->code == sf::Keyboard::Key::Right);
            shopControls.select = (keyPressed->code == sf::Keyboard::Key::Enter);
            


            game.getShop(0).handleInput(shopControls, game.getPlayers()[0]);


            if (keyPressed->code == sf::Keyboard::Key::E) {
                game.setShopActive(false); 
            }
        }
    }
}

void IHM::renderShop() {
    window.clear(sf::Color(25, 25, 45)); 

    Shop& shop = game.getShop(0);
    Player& player = game.getPlayers()[0];


    sf::Text uiText(font);
    uiText.setCharacterSize(24);
    uiText.setFillColor(sf::Color::Yellow);
    uiText.setString("GOLD: " + std::to_string(player.getGold()));
    

    sf::FloatRect bounds = uiText.getGlobalBounds();
    uiText.setPosition({400.f - bounds.size.x / 2.f, 50.f});
    window.draw(uiText);


    float slotW = 160.f;
    float slotH = 220.f;
    float gap = 20.f;
    float totalW = (4 * slotW) + (3 * gap);
    float startX = 400.f - (totalW / 2.f);

    for (int i = 0; i < 4; i++) {
        Item item = shop.getItemAt(i);
        sf::Vector2f pos = {startX + i * (slotW + gap), 250.f};

        // Fond du slot
        sf::RectangleShape rect({slotW, slotH});
        rect.setPosition(pos);
        rect.setFillColor(sf::Color(50, 50, 70));

        // Bordure de sélection (Curseur)
        if (shop.getCurrentCursor() == i) {
            rect.setOutlineColor(sf::Color::Yellow);
            rect.setOutlineThickness(4.f);
        } else {
            rect.setOutlineColor(sf::Color(100, 100, 100));
            rect.setOutlineThickness(1.f);
        }
        window.draw(rect);


        if (item.name != "None") {

            uiText.setString(item.name);
            uiText.setCharacterSize(14);
            uiText.setFillColor(sf::Color::White);
            uiText.setPosition({pos.x + 10.f, pos.y + 15.f});
            window.draw(uiText);


            uiText.setString(std::to_string(item.price) + " G");
            uiText.setFillColor(sf::Color::Yellow);
            uiText.setPosition({pos.x + slotW / 2.f - 20.f, pos.y + slotH - 40.f});
            window.draw(uiText);
        } else {

            uiText.setString("Sold");
            uiText.setFillColor(sf::Color(150, 50, 50));
            uiText.setPosition({pos.x + 40.f, pos.y + 100.f});
            window.draw(uiText);
        }
    }


    uiText.setString("Select your Item");
    uiText.setCharacterSize(16);
    uiText.setFillColor(sf::Color(180, 180, 180));
    uiText.setPosition({400.f - uiText.getGlobalBounds().size.x / 2.f, 600.f});
    window.draw(uiText);

    window.display();
}