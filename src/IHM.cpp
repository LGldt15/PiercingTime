#include "IHM.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Inventory.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include "../assets/Background/Background.h"
#include "../assets/Enemy/gromgroi.h"
#include "../assets/Player/player.h"
#include "../assets/Bullet/caillou.h"
#include "../assets/Items/dino_essence.h"
//#include "../assets/play.h"
#include "../assets/Icon.h"
#include "iostream"
#include "Item.h"

//constante pour les inputs souris
const sf::FloatRect nextBtnRect({650.f, 700.f}, {120.f, 50.f});


IHM::IHM(){
    winWidth=800;
    winHeight=800;
    sf::Vector2<unsigned int> size={winWidth,winHeight};
    window=sf::RenderWindow(sf::VideoMode(size), "Piercing Time");
// Y avait une segfault psk c t mal initialise les tableaux et du coup le destructeur
// il comprennait pas quoi supp 
    for (int i = 0; i < 2; i++)  playerSprites[i] = nullptr;
    for (int i = 0; i < 4; i++)  enemySprites[i] = nullptr;
    for (int i = 0; i < 9; i++)  mapSprites[i] = nullptr;
    for (int i = 0; i < 9; i++)  bulletSprites[i] = nullptr;
    for (int i = 0; i < 10; i++) buttonSprites[i] = nullptr;

    //Icon de l'app
    sf::Image Icon;
    if (Icon.loadFromMemory(Icon_png, Icon_png_len)) {
        window.setIcon({Icon.getSize().x, Icon.getSize().y}, Icon.getPixelsPtr());
    }
    

    mapSprites[0]=nullptr;
    if(mapTypes[0].loadFromMemory(Background_png,Background_png_len)){
        mapSprites[0]=new sf::Sprite(mapTypes[0]);
    }

    sf::Vector2f sizeM={800.0f/1200,800.0f/1200};
    mapSprites[0]->setScale(sizeM);

    if(playerTypes[0].loadFromMemory(player_png,player_png_len)){
        playerSprites[0]=new sf::Sprite(playerTypes[0]);
    }

    if (enemyTypes[0].loadFromMemory(gromgroi_png,gromgroi_png_len)){
        enemySprites[0]=new sf::Sprite(enemyTypes[0]);
    }

    if(bulletTypes[0].loadFromMemory(caillou_png,caillou_png_len)){
        bulletSprites[0]=new sf::Sprite(bulletTypes[0]);
    }

    //LE BOUTON DE JEU N EST PLUS UN PNG MAIS UN RECT SFML
    //if(buttons[0].loadFromMemory(Play_jpg,Play_jpg_len)){
    //    buttonSprites[0]=new sf::Sprite(buttons[0]);
    //}
    //buttonSprites[0]->setPosition({100.0f,300.0f});


    if(!font.openFromFile("./assets/fonts/font.ttf")) {
        std::cout << "Erreur avec le font" << std::endl;
    }
    
    showInventory=false;
}

void IHM::getInputs(){
    inputs.up=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    inputs.down=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
    inputs.right=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    inputs.left=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    inputs.pause=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
    inputs.select=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    inputs.tab=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab);


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

 
    if (!game.isOver()) {
        window.draw(*mapSprites[0]);
        
        // Dessiner les joueurs
        Player* p = game.getPlayers();
        for(int i = 0; i < game.getNbJoueur(); i++){
            sf::Vector2f pos = {p[i].getPosition().posX, p[i].getPosition().posY};
            playerSprites[0]->setPosition(pos);
            window.draw(*playerSprites[0]);
        }

        Enemy* enemyzero = game.getEnemies();
        for(int i = 0; i < MAX_ENEMY; i++){ 
            if(enemyzero[i].isAlive){
                sf::Vector2u s = enemyTypes[enemyzero[i].sprite].getSize();
                sf::Vector2f si = {100.0f/s.x, 60.0f/s.y};
                enemySprites[0]->setScale(si);
                sf::Vector2f pos = {enemyzero[i].position.posX, enemyzero[i].position.posY};
                enemySprites[0]->setPosition(pos);
                window.draw(*enemySprites[0]);
            }
        }


        Bullet* bulletzero = game.getBullets();
        for(int i = 0; i < game.getNbBullets(); i++){
            if (bulletzero[i].damage != 0){
                sf::Vector2f pos = {bulletzero[i].pos.posX, bulletzero[i].pos.posY};
                bulletSprites[bulletzero[i].getSprite()]->setPosition(pos);
                window.draw(*bulletSprites[0]);
            }
        }


        if (showInventory) {
            sf::RectangleShape overlayBG({300.f, 70.f});
            overlayBG.setFillColor(sf::Color(0, 0, 0, 200)); 
            overlayBG.setPosition({150.f, 350.f}); 
            window.draw(overlayBG);
            drawInventoryOverlay(160.f, 360.f);
        }
    }
    else {
        sf::Text gameOverText(font);
        gameOverText.setString("GAME OVER\nAppuie sur ESPACE pour recommencer");
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setStyle(sf::Text::Bold);
        

        sf::FloatRect bounds = gameOverText.getGlobalBounds();
        gameOverText.setPosition({400.f - bounds.size.x / 2.f, 350.f});
        
        window.draw(gameOverText);
    }

    window.display(); 
}


void IHM::gameLoop() {
    while (window.isOpen()) {
        
        if (game.isPlayerDead()) {
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                game.restart();
            }
            renderMap(); 
        }
        
        else if (game.isInShop()) {
            handleShopInput();
            renderShop();
        }
        
        else {
           
            if (game.isTimeUp()) {
                game.setShopActive(true);
                game.resetTimer(); 
            }


            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) window.close();
                

                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->code == sf::Keyboard::Key::Tab) {
                        showInventory = !showInventory;
                    }
                }
            }

            getInputs();
            if (!showInventory) {
                game.update(inputs, winWidth, winHeight);
            }
            
            renderMap();
        }
    }
}




void IHM::renderMenu() {
    window.clear(sf::Color(20, 20, 30)); // Fond bleu nuit sombre

    // --- 1. TITRE DU JEU ---
    sf::Text title(font); 
    title.setString("PIERCING TIME");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    
    // Centrage automatique du titre
    sf::FloatRect titleBounds = title.getGlobalBounds();
    title.setPosition({400.f - titleBounds.size.x / 2.f, 150.f});
    window.draw(title);

    // --- 2. OPTIONS DU MENU ---
    std::string options[] = {"PLAY", "ONLINE", "LEAVE"};
    
    for (int i = 0; i < 3; i++) {
        float yPos = 400.f + (i * 100.f);
        
        // Fond du bouton (Rectangle)
        sf::RectangleShape buttonBox({250.f, 60.f});
        buttonBox.setPosition({400.f - 125.f, yPos});
        
        // Texte du bouton (SFML 3 style)
        sf::Text optText(font);
        optText.setString(options[i]);
        optText.setCharacterSize(30);
        
        // Interaction visuelle selon la sélection
        if (mainMenu.getSelected() == i) {
            buttonBox.setFillColor(sf::Color(80, 80, 120)); // Surbrillance
            buttonBox.setOutlineColor(sf::Color::Cyan);
            buttonBox.setOutlineThickness(3.f);
            optText.setFillColor(sf::Color::Cyan);
        } else {
            buttonBox.setFillColor(sf::Color(40, 40, 60));
            buttonBox.setOutlineColor(sf::Color::White);
            buttonBox.setOutlineThickness(1.f);
            optText.setFillColor(sf::Color::White);
        }

        window.draw(buttonBox);
        
        // Centrage du texte dans son rectangle
        sf::FloatRect textBounds = optText.getGlobalBounds();
        optText.setPosition({400.f - textBounds.size.x / 2.f, yPos + 10.f});
        window.draw(optText);
    }

    // --- 3. TEXTE D'AIDE ---
    sf::Text help(font);
    help.setString("Utilisez les FLECHES pour choisir et ESPACE pour valider");
    help.setCharacterSize(16);
    help.setFillColor(sf::Color(150, 150, 150));
    sf::FloatRect helpBounds = help.getGlobalBounds();
    help.setPosition({399.f - helpBounds.size.x / 2.f, 699.f});
    window.draw(help);

    window.display();
}

void IHM::playerSelect() {

}

void IHM::app(){
    window.setFramerateLimit(60);
    
    while (window.isOpen()){
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();


            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Up) {
                    mainMenu.up(); 
                }
                if (keyPressed->code == sf::Keyboard::Key::Down) {
                    mainMenu.down();
                }
                if (keyPressed->code == sf::Keyboard::Key::Enter || keyPressed->code == sf::Keyboard::Key::Space) {
                    int choice = mainMenu.getSelected();
                    if (choice == 0) gameLoop();   
                    if (choice == 1) { std::cout<<"not yet..."<<std::endl;};
                    if (choice == 2) window.close();

                }
            }
        }
        
        renderMenu();
    }
}

//PARTIE shop

void IHM::handleShopInput() {
    while (const std::optional event = window.pollEvent()) {
        

        if (event->is<sf::Event::Closed>()) {
            window.close();
        }


        if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseEvent->button == sf::Mouse::Button::Left) {


            sf::Vector2f mousePos = window.mapPixelToCoords(mouseEvent->position);


                sf::FloatRect nextBtnRect({650.f, 700.f}, {120.f, 50.f});

                if (nextBtnRect.contains(mousePos)) {
                    game.setShopActive(false); 
                    game.resetTimer();         
                }
            }
        }


        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            

            Controls shopControls;
            shopControls.left   = (keyPressed->code == sf::Keyboard::Key::Left);
            shopControls.right  = (keyPressed->code == sf::Keyboard::Key::Right);
            shopControls.select = (keyPressed->code == sf::Keyboard::Key::Enter || keyPressed->code == sf::Keyboard::Key::Space);
            

            game.getShop(0).handleInput(shopControls, game.getPlayers()[0]);


            if (keyPressed->code == sf::Keyboard::Key::N || keyPressed->code == sf::Keyboard::Key::E) {
                game.setShopActive(false); 
                game.resetTimer();
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


        sf::RectangleShape rect({slotW, slotH});
        rect.setPosition(pos);
        rect.setFillColor(sf::Color(50, 50, 70));


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


    float goldErrorTimer = 0.0f; 
        // À la fin de renderShop(), juste avant window.display()
    if (player.getGold() < shop.getItemAt(shop.getCurrentCursor()).price && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
       goldErrorTimer = 3.0f; // Affiche le message pendant 2 secondes
    }

    if (goldErrorTimer > 0) {
        uiText.setString("PAS ASSEZ D'OR !");
        uiText.setFillColor(sf::Color::Red);
        uiText.setCharacterSize(20);
        // On le place au dessus des slots
        uiText.setPosition({400.f - uiText.getGlobalBounds().size.x / 2.f, 200.f});
        window.draw(uiText);
        goldErrorTimer -= 0.016f; // On décrémente (environ 1/60ème de seconde)
    }

    sf::RectangleShape nextBtn({120.f, 50.f});
    nextBtn.setPosition({650.f, 700.f});
    nextBtn.setFillColor(sf::Color(70, 70, 200)); // Couleur bleue pour changer
    nextBtn.setOutlineThickness(2.f);
    nextBtn.setOutlineColor(sf::Color::White);
    window.draw(nextBtn);

    sf::Text nextText(font);
    nextText.setString("NEXT (N)"); // Indique au joueur quelle touche presser
    nextText.setCharacterSize(20);
    nextText.setFillColor(sf::Color::White);
    nextText.setPosition({670.f, 715.f});
    window.draw(nextText);
    window.display();
}




//_________inventaire_________

void IHM::drawInventoryOverlay(float startX, float startY) {
    float slotSize = 45.f;
    float padding = 10.f;

    Player& player = game.getPlayers()[0];
    const Inventory& inv = player.getInventory();
    int nbItems = inv.getNbItems();

    for (int i = 0; i < 5; i++) {

        sf::RectangleShape slot({slotSize, slotSize});
        slot.setPosition({startX + (i * (slotSize + padding)), startY});
        slot.setFillColor(sf::Color(30, 30, 50, 200));
        slot.setOutlineThickness(2.f);
        slot.setOutlineColor(sf::Color(150, 150, 150));
        window.draw(slot);


        if (i < nbItems) {

            float itemMargin = 10.f;
            sf::RectangleShape itemIcon({slotSize - (itemMargin * 2), slotSize - (itemMargin * 2)});
            itemIcon.setFillColor(sf::Color::Yellow);
            

            itemIcon.setPosition({
                slot.getPosition().x + itemMargin, 
                slot.getPosition().y + itemMargin
            });
            
            window.draw(itemIcon);
        }
    }
}