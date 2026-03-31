#include "IHMServeur.h"
#include "Game.h"
#include "Player.h"
#include <cstring>
#include <iostream>


IHMServeur::IHMServeur(int p){
    port=p;
}

void IHMServeur::run(){
    sf::TcpListener listener;
    if(listener.listen(port)==sf::Socket::Status::Done){
        std::cout<<"all good\n";
    }
    // This manages the list of all sockets
    sf::SocketSelector selector;
    selector.add(listener);
    if(selector.isReady(listener)){
        std::cout<<"huh?\n";
    }
    // Keep a list to store our active clients
    std::list<sf::TcpSocket*> clients;

    std::cout << "MultiPlayer Server running on port " <<port<< std::endl;
    while (true) {
        // Wait until any socket has an event
        if (selector.wait()) {
            int nbUpdate=0;
            // 1. Check if the listener has a new connection
            if (selector.isReady(listener)) {
                sf::TcpSocket* client = new sf::TcpSocket;
                if (listener.accept(*client) == sf::Socket::Status::Done) {
                    clients.push_back(client);
                    selector.add(*client); // Add new client to the selector
                    std::cout << "New client joined! Total: " << clients.size() << std::endl;
                    game.setNbPlayers(game.getNbJoueur()+1);
                    sf::Packet responsePacket;
                    responsePacket.append(&game, sizeof(Game));
                    client->send(responsePacket);
                } else {
                    delete client;
                }
            } 
            
            // 2. Check all existing clients for data
            else {
                for (auto it = clients.begin(); it != clients.end(); ) {
                    //std::cout<<"sending data\n";
                    sf::TcpSocket& client = **it;
                    if (selector.isReady(client)) {
                        Player* currentPlayer=game.getPlayers();
                        sf::Packet packet;
                        if (client.receive(packet) == sf::Socket::Status::Done) {
                            nbUpdate++;
                            // Move the pointer forward by 4 bytes to skip the size header
                            const char* rawData = static_cast<const char*>(packet.getData());

                            // 3. Copy the ID (First part of the message)
                            int id;
                            std::memcpy(&id, rawData, sizeof(int));

                            // 4. Copy the Player (Starts after the ID)
                            // We add sizeof(int) to the pointer to move past the ID we just read
                            std::memcpy(&game.getPlayers()[id-1], rawData + sizeof(int), sizeof(Player));
                            //std::cout << "Message received from client "<<client.getRemoteAddress()->toString()<<"on server "<<port <<" : " << id<< std::endl;
                            

                            sf::Packet responsePacket;
                            responsePacket.append(&game, sizeof(Game));
                            client.send(responsePacket);



                            it++; 
                        } else {
                            // Client disconnected
                            std::cout << "Client disconnected." << std::endl;
                            selector.remove(client);
                            delete *it;
                            it = clients.erase(it); // Remove from list
                        }
                    } else {
                        it++;
                    }
                }
                game.update();
            }   
        }  
    }
}