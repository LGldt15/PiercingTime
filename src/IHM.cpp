#include "IHM.h"
#include <SFML/Network.hpp>
#include "Bullet.h"
#include "Enemy.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstring>
#include <string>
#include "../assets/Background.h"
#include "../assets/gromgroi.h"
#include "../assets/player.h"
#include "../assets/caillou.h"
#include "../assets/play.h"

#include "Inventory.h"
#include "Player.h"
#include "iostream"


IHM::IHM(){
    winWidth=800;
    winHeight=800;
    sf::Vector2<unsigned int> size={winWidth,winHeight};
    window=sf::RenderWindow(sf::VideoMode(size), "My SFML Window");


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

    if(buttons[0].loadFromMemory(play_jpg,play_jpg_len)){
        buttonSprites[0]=new sf::Sprite(buttons[0]);
    }
    buttonSprites[0]->setPosition({100.0f,300.0f});
    
    if(!font.openFromFile("./assets/font.ttf")) {
        std::cout << "Erreur avec le font" << std::endl;
    }
}

void IHM::getInputs(){
    inputs[idMulti].up=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    inputs[idMulti].down=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
    inputs[idMulti].right=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    inputs[idMulti].left=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    inputs[idMulti].pause=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
    inputs[idMulti].select=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
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
    window.display();
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
void IHM::gameLoop(){
    while (window.isOpen()){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            app();
                
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
        game.update(inputs[0], winWidth, winHeight);
        renderMap();
    }}
}

void IHM::gameLoopMulti() {
    sf::TcpSocket socket;
    sf::IpAddress ip(10,42,147,46);
    int room;
    // 1. Initial Connection to Dispatcher
    if (socket.connect(ip, 53000) != sf::Socket::Status::Done) {
        return;
    }

    // --- PHASE 1: MENU (Dispatcher) ---
    bool inMenu = true;
    while (inMenu && window.isOpen()) {
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        // Get input (e.g., "new")
        std::cout<<"select:";
        std::string choice ; 
        std::getline(std::cin, choice);
        sf::Packet p;
        p << choice;
        socket.send(p);

        // The server won't send back a Port anymore. 
        // It will just start sending Game Data or a "Success" packet.
        sf::Packet response;
        if (socket.receive(response) == sf::Socket::Status::Done) {
            std::string serverMsg;

            response >> serverMsg;

            std::cout << "Dispatcher says: " << serverMsg << std::endl; 

            if(serverMsg[0]=='r') {
                inMenu = false; // We received our first game state or confirmation
                std::string roomId;
                roomId=serverMsg[1];//+serverMsg[2]+serverMsg[3]
                std::cout<<roomId;
                room=std::stoi(roomId);
            }
        }
    }

    // --- PHASE 2: GAME (Room Thread) ---
    // Notice: NO NEW CONNECTION HERE. Use the same 'socket'.
    std::cout<<"out of menu\n";
    idMulti = -1;
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        // ... standard game loop events ...
        sf::Packet receivePacket;
        // The Room Thread is now the one sending this data
        if (socket.receive(receivePacket) == sf::Socket::Status::Done) {
            // Use your memcpy logic or packet extraction

            std::memcpy(&game, receivePacket.getData(), sizeof(Game));
            
            if (idMulti == -1) {
                idMulti = game.getNbJoueur()-1;
            }
        }

        // Send your inputs back to the Room Thread
        if (idMulti != -1) {
            getInputs();
            sf::Packet sendPacket;
            sendPacket.append(&idMulti, sizeof(int));
            sendPacket.append(&inputs, sizeof(Controls));
            socket.send(sendPacket);
        }
        renderMap();
    }
}


void IHM::renderMenu() {
    window.clear(sf::Color(20, 20, 30)); // Fond bleu nuit sombre

    // --- 1. TITRE DU JEU ---
    sf::Text title(font); // SFML 3 : On passe la font au constructeur
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
    window.setFramerateLimit(30);
    bool selected=true;
    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        getInputs();
        if (inputs->up) {
            mainMenu.up(); 
        }
        if (inputs->down) {
            mainMenu.down();
        }
        if (inputs->select) {
            int choice = mainMenu.getSelected();
            if (choice == 0) gameLoop();   
            if (choice == 1) gameLoopMulti();
            if (choice == 2) window.close();
        }
        renderMenu();
    }
}