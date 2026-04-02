#include <SFML/Network.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <list>
#include <cstdlib>
#include <string>
#include "IHMServeur.h"

std::vector<IHMServeur*> activeRooms;
int nbRooms=0;
int main() {
    sf::TcpListener listener;
    listener.listen(53000);

    // This manages the list of all sockets
    sf::SocketSelector selector;
    selector.add(listener);

    // Keep a list to store our active clients
    std::list<sf::TcpSocket*> clients;

    std::cout << "Dispatcher Server running..." << std::endl;

    int nextPort=53001;

    while (true) {
        // Wait until any socket has an event
        if (selector.wait()) {
            
            // 1. Check if the listener has a new connection
            if (selector.isReady(listener)) {
                sf::TcpSocket* client = new sf::TcpSocket;
                if (listener.accept(*client) == sf::Socket::Status::Done) {
                    clients.push_back(client);
                    selector.add(*client); // Add new client to the selector
                    std::cout << "New client joined! Total: " << clients.size() << std::endl;
                    std::string reply = "Message received!";
                } else {
                    delete client;
                }
            } 
            
            // 2. Check all existing clients for data
            else {
                for (auto it = clients.begin(); it != clients.end(); ) {
                    sf::TcpSocket& client = **it;
                    if (selector.isReady(client)) {
                        sf::Packet packet;
                        if (client.receive(packet) == sf::Socket::Status::Done) {
                            std::string message;
                            packet >> message;
                            std::cout << "Message received from client "<<client.getRemoteAddress()->toString()<<" : " << message << std::endl;
                            
                            if (message == "new") {
                                sf::TcpSocket* clientPtr = *it;
                                                        
                                // 1. STOP the dispatcher from watching this socket
                                selector.remove(*clientPtr);
                                                        
                                // 2. Remove from the dispatcher's local list so it isn't deleted here
                                it = clients.erase(it);
                                                        
                                // 3. Create the room object (on the Heap)
                                IHMServeur* newRoom = new IHMServeur(nbRooms); 
                                nbRooms++;
                                                        
                                // 4. Store it so others can join later
                                activeRooms.push_back(newRoom);
                                                        
                                // 5. Hand the socket over and let it start its own thread
                                newRoom->startWithClient(clientPtr);
                                                        
                                std::cout << "Created Room #" << activeRooms.size() << " and handed off player." << std::endl;
                                                        
                                continue; // Skip the it++ because we already erased 'it'
                            }                              
                            else if (message=="info") {
                                sf::Packet responsePacket;
                                std::string mess;
                                mess+="available servers :\n";
                                if(true){
                                    mess+="    no rooms to create a room send 'new'\n";
                                }
                                for(int i=0;i<activeRooms.size();i+=2){
                                    mess+="    "+ std::to_string(i)+"\n";
                                }
                                responsePacket<<mess;
                                client.send(responsePacket);
                            }
                            else if (std::stoi(message)>=0 && std::stoi(message)<activeRooms.size()) {
                                int roomIndex=std::stoi(message);
                                sf::TcpSocket* clientPtr = *it;

                                // Hand-off logic again
                                selector.remove(*clientPtr);
                                it = clients.erase(it);

                                // Call a new method in IHMServeur to add a player to an existing loop
                                activeRooms[roomIndex]->addPlayer(clientPtr);

                                std::cout << "Player joined existing Room #" << roomIndex << std::endl;
                                continue;
                            }  
                            else{
                                std::string reply = "Message received!";
                                sf::Packet responsePacket;
                                responsePacket <<reply;
                                client.send(responsePacket);
                            }                
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
            }
        }
    }
    return 0;
}