#include "IHM.h"
#include <SFML/Network.hpp>
#include "Bullet.h"
#include "Enemy.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstring>
#include <string>
#include "../assets/Background/Background.h"
#include "../assets/Enemy/gromgroi.h"
#include "../assets/Player/player.h"
#include "../assets/Bullet/caillou.h"
//#include "../assets/play.h"
#include "../assets/fonts/font.h"

#include "Inventory.h"
#include "Player.h"
#include "iostream"


IHM::IHM(){
    winWidth=800;
    winHeight=800;
    idMulti=0;
    sf::Vector2<unsigned int> size={winWidth,winHeight};
    window=sf::RenderWindow(sf::VideoMode(size), "My SFML Window");

    for (int i = 0; i < 2; i++)  playerSprites[i] = nullptr;
    for (int i = 0; i < 4; i++)  enemySprites[i] = nullptr;
    for (int i = 0; i < 9; i++)  mapSprites[i] = nullptr;
    for (int i = 0; i < 9; i++)  bulletSprites[i] = nullptr;

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
    
    if(!font.openFromMemory(font_ttf, font_ttf_len)) {
        std::cout << "Erreur avec le font" << std::endl;
    }
    for(int i=0;i<4;i++){
        game.getShop(i).refreshShop();
    }
}
void IHM::getInputs(){
    inputs[idMulti].up=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    inputs[idMulti].down=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
    inputs[idMulti].right=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    inputs[idMulti].left=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    inputs[idMulti].pause=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
    inputs[idMulti].select=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    inputs[idMulti].tab=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab);
    inputs[idMulti].back=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
    inputs[idMulti].next=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N);


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

    Shop& shop = game.getShop(idMulti);
    Player& player = game.getPlayers()[idMulti];


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


        if (item.name[0] != 'N') {

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
    nextText.setString("NEXT (Nx2)"); // Indique au joueur quelle touche presser
    nextText.setCharacterSize(20);
    nextText.setFillColor(sf::Color::White);
    nextText.setPosition({670.f, 715.f});
    window.draw(nextText);
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
    if(showInventory){
        drawInventoryOverlay(100, 100);
    }
    window.display(); 
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


void IHM::handleShopInput() {
    game.getShop(idMulti).handleInput(inputs[idMulti], game.getPlayers()[idMulti]);
}


void IHM::gameLoop(){
    while (window.isOpen()) {
        
        getInputs();
        if (game.isPlayerDead()) {
            
            if (inputs[idMulti].next) {
                game.restart();
            }
            renderMap(); 
        }
        
        else if (game.isInShop()) {
            std::cout<<"here2\n";
            handleShopInput();
            renderShop();           
            if (inputs[idMulti].next) {
                game.resetTimer(); 
                game.restart();
            }
        }
        
        else {
           
            if (game.isTimeUp()) {
                std::cout<<"here\n";
                game.setShopActive(true);
                game.resetTimer(); 
            }

            // Gestion des événements
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) window.close();
            }
            showInventory=false;
            if(inputs[idMulti].tab){
                showInventory=true;
            }
            if (!showInventory) {
                game.update(inputs[idMulti],800,800);
            }
            renderMap();
        }
    }
}

void IHM::gameLoopMulti() {
    sf::TcpSocket socket;
    sf::IpAddress ip(127,0,0,1);
    int room;
    // 1. Initial Connection to Dispatcher
    std::cout<<"attempting connexion\n";
    if (socket.connect(ip, 53000) != sf::Socket::Status::Done) {
        std::cout<<"falled to connect\n";
        return;
    }
    std::cout<<"connected";
    // --- PHASE 1: MENU (Dispatcher) ---
    bool releasedSelect=false;
    if (!releasedSelect && !inputs[idMulti].select){
        releasedSelect=true;
    }
    bool inMenu = true;
    int selected=0;
    while (inMenu && window.isOpen()){
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color(20, 20, 30)); // Fond bleu nuit sombre
        sf::Text title(font); // SFML 3 : On passe la font au constructeur
        title.setString("Online Play");
        title.setCharacterSize(60);
        title.setFillColor(sf::Color::Yellow);
        title.setStyle(sf::Text::Bold);
        sf::FloatRect titleBounds = title.getGlobalBounds();
        title.setPosition({400.f - titleBounds.size.x / 2.f, 150.f});
        window.draw(title);
        std::string options[] = {"Create Room", "Join Room"};


        getInputs();
        if (!releasedSelect && !inputs[idMulti].select){
            releasedSelect=true;
        }
        if (inputs[idMulti].up || inputs[idMulti].down){
            selected=(selected+1)%2;
        }
        if(releasedSelect && inputs[idMulti].select){
            inMenu=false;
        }
        for (int i = 0; i < 2; i++) {
            float yPos = 400.f + (i * 100.f);

            // Fond du bouton (Rectangle)
            sf::RectangleShape buttonBox({250.f, 60.f});
            buttonBox.setPosition({400.f - 125.f, yPos});

            // Texte du bouton (SFML 3 style)
            sf::Text optText(font);
            optText.setString(options[i]);
            optText.setCharacterSize(30);

            // Interaction visuelle selon la sélection
            if (selected == i) {
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
        window.display();
    }

    if(selected==0){
        sf::Packet p;
        p << "new";
        socket.send(p);
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
    else{
        inMenu=true;
        releasedSelect=false;
        int rooms[11]={0,0,0,0,0,0,0,0,0,0};
        sf::Packet p;
        p << "info";
        socket.send(p);
        sf::Packet response;
        std::cout<<"packet sent waitong for response\n";
        if (socket.receive(response) == sf::Socket::Status::Done) {
            std::cout<<"sent 'info' awaiting response\n";

                        
                        
            // 3. Copy the ID (First part of the message
            
            // 4. Copy the Player (Starts after the ID)
            
            // We add sizeof(int) to the pointer to move past the ID we just read
            
            std::memcpy(&rooms, response.getData(), sizeof(int[11]));
            std::cout << "\nDispatcher says: " << rooms[0] << std::endl; 
            //ON SELECT LA ROOM
            while (inMenu && window.isOpen()) {
                while (const std::optional event = window.pollEvent())
                {
                    // Close window: exit
                    if (event->is<sf::Event::Closed>())
                        window.close();
                }
                // Get input (e.g., "new")
            
                //AFFICHAGE
            
                window.clear(sf::Color(20, 20, 30)); // Fond bleu nuit sombre
                sf::Text title(font); // SFML 3 : On passe la font au constructeur
                title.setString("ROOMS");
                title.setCharacterSize(60);
                title.setFillColor(sf::Color::Yellow);
                title.setStyle(sf::Text::Bold);
                sf::FloatRect titleBounds = title.getGlobalBounds();
                title.setPosition({400.f - titleBounds.size.x / 2.f, 150.f});
                window.draw(title);
                    
                    
                getInputs();
                if (!releasedSelect && !inputs[idMulti].select){
                    releasedSelect=true;
                }
                if (inputs[idMulti].up || inputs[idMulti].down){
                    selected=(selected+1)%rooms[0];
                }
                if(releasedSelect && inputs[idMulti].select){
                    inMenu=false;
                }
                for (int i = 0; i < rooms[0]; i++) {
                    float yPos = 400.f + (i * 100.f);
                
                    // Fond du bouton (Rectangle)
                    sf::RectangleShape buttonBox({250.f, 60.f});
                    buttonBox.setPosition({400.f - 125.f, yPos});
                
                    // Texte du bouton (SFML 3 style)
                    sf::Text optText(font);
                    optText.setString(std::to_string(rooms[i+1]));
                    optText.setCharacterSize(30);
                
                    // Interaction visuelle selon la sélection
                    if (selected == i) {
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
                window.display();
            }
            sf::Packet roomM;
            std::cout<<selected<<std::endl;
            roomM<<std::to_string(selected);
            socket.send(roomM);


            sf::Packet roomC;
            std::cout<<"packet sent waitong for response\n";
            if (socket.receive(roomC) == sf::Socket::Status::Done) {
                std::string serverMsg;
                response >> serverMsg;
                if(serverMsg[0]=='r') {
            
                    inMenu = false; // We received our first game state or confirmation
                    std::string roomId;
                    roomId=serverMsg[1];//+serverMsg[2]+serverMsg[3]
                    std::cout<<roomId;
                    room=std::stoi(roomId);
                }
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
                std::cout<<idMulti<<std::endl;
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
        if (game.isInShop()) {
            renderShop();      
        }else{
            renderMap();
        }
    }
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

