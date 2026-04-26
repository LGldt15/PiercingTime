#include "IHMServeur.h"
#include "Game.h"
#include "Inventory.h"
#include "Player.h"
#include <SFML/Network/Packet.hpp>
#include <cstring>
#include <iostream>
#include <string>

IHMServeur::IHMServeur(int i){
    id = i;
    running=true;
}


void IHMServeur::handleShopInput() {
    for(int i=0;i<game.getNbJoueur();i++){
        game.getShop(i).handleInput(inputs[i],game.getPlayers()[i] );
    }
}

void IHMServeur::executionLoop() {
    std::cout<<"started loop\n";
    bool ready[4]={false,false,false,false};
    while (true) {
        // Use a timeout so the thread doesn't freeze if no one is sending data
        roomMutex.lock();
        float dt=gameClock.restart().asSeconds();
        if (selector.wait()) {
            
            for (auto it = clients.begin(); it != clients.end(); ) {
                sf::TcpSocket& client = **it;
                if (selector.isReady(client)) {
                    sf::Packet packet;
                    sf::Socket::Status status = client.receive(packet);

                    if (status == sf::Socket::Status::Done) {

                        Player* currentPlayer=game.getPlayers();
                        
                        
                        
                        // Move the pointer forward by 4 bytes to skip the size header
                        
                        const char* rawData = static_cast<const char*>(packet.getData());
                        
                        
                        // 3. Copy the ID (First part of the message)
                        
                        int id;
                        
                        std::memcpy(&id, rawData, sizeof(int));
                        
                        // 4. Copy the Player (Starts after the ID)
                        
                        // We add sizeof(int) to the pointer to move past the ID we just read
                        
                        std::memcpy(&inputs[id], rawData + sizeof(int), sizeof(Controls));
                        
                        //std::cout << "Message received from client "<<client.getRemoteAddress()->toString()<<client.getRemotePort()<<std::endl;
                        it++;

                        sf::Packet response;
                        response.append(&game, sizeof(Game)); 
                        client.send(response);
                        
                    } else if (status == sf::Socket::Status::Disconnected) {
                        selector.remove(client);
                        delete *it;
                        it = clients.erase(it);
                    } else {
                        it++;
                    }
                } else {
                    it++;
                }
            }
            
        }
        roomMutex.unlock();
        // Update physics/game logic if the game has started
        if(!game.isInShop()){
            game.update(inputs,dt);
        }else{
            for(int i=0;i<game.getNbJoueur();i++)
                game.getShop(i).refreshShop();
            handleShopInput();
            game.setShopActive(false);
            for(int i=0;i<game.getNbJoueur();i++){
                if (inputs[i].next){
                    ready[i]=true;
                }
                if(!ready[i]){
                    game.setShopActive(true);
                }
            }
            if(!game.isInShop()){
                game.resetTimer();
                game.restart();
                for (int i=0;i<4;i++){
                    ready[i]=false;
                }
            }

        }
        
        
        // If all players left, stop the room
        if (clients.empty()) running = false;
    }
    delete this; // Clean up the room object memory when the thread finishes
}


void IHMServeur::startWithClient(sf::TcpSocket* creator) {
    clients.push_back(creator);
    selector.add(*creator);
    
    // Increment player count in your logic
    game.setNbPlayers(1); 

    // Launch the thread. 'this' allows the thread to access class members.
    roomThread = std::thread(&IHMServeur::executionLoop, this);
    roomThread.detach(); 
    sf::Packet responsePacket;
    std::string mess="r"+std::to_string(id);
    responsePacket<<mess;
    creator->send(responsePacket);

    sf::Packet response;
    response.append(&game, sizeof(Game)); 
    creator->send(response);
}

void IHMServeur::addPlayer(sf::TcpSocket* player){
    std::lock_guard<std::mutex> lock(roomMutex);

    clients.push_back(player);
    selector.add(*player);
    
    // Increment player count in your logic
    game.setNbPlayers(game.getNbJoueur()+1); 
    sf::Packet responsePacket;
    std::string mess="r"+std::to_string(id);
    responsePacket<<mess;
    player->send(responsePacket);

    sf::Packet response;
    response.append(&game, sizeof(Game)); 
    player->send(response);
}