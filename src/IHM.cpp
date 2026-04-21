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
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        getInputs();
        game.update(inputs[0], winWidth, winHeight);
        renderMap();
    }
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
            game.getPlayers()[idMulti].move(inputs[idMulti],800, 800);
            game.getPlayers()[idMulti].doWeStart(inputs[0]);
            sf::Packet sendPacket;
            sendPacket.append(&idMulti, sizeof(int));
            sendPacket.append(&game.getPlayers()[idMulti], sizeof(Player));
            socket.send(sendPacket);
        }
        renderMap();
    }
}

void IHM::renderMenu() {
    window.clear(sf::Color::Black);
    window.draw(*mapSprites[0]);
    switch(mainMenu.getSelected()){
        case 0:{
            window.draw(*buttonSprites[0]);
            break;
        }
    }
    window.display(); 
}

void IHM::playerSelect() {

}

void IHM::app(){
    bool selected=true;
    int s=-1;
    window.setFramerateLimit(30);
    while (window.isOpen()){
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        getInputs();
        if (inputs[0].select){
            s=mainMenu.getSelected();
            selected=false;
        }
        if(selected)renderMenu();
        if(s==0){
            gameLoopMulti();
        }
    }
}