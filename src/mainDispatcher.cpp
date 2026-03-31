#include <SFML/Network.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <list>
#include <cstdlib>
#include <string>

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
                                #include <cstdlib>
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
                                std::string port=std::to_string(nextPort);
                                // 1. Combine the command and the variable into one string
                                std::string command = "kitty ./server " + port+'&';

                                // 2. Pass it to system() using .c_str()
                                std::system(command.c_str());
                                sf::Packet responsePacket;
                                std::string mess='0'+std::to_string(nextPort);
                                responsePacket << mess;
                                client.send(responsePacket);

                                nextPort+=2;
                            }
                            else if (message=="info") {
                                sf::Packet responsePacket;
                                std::string mess;
                                mess+="available servers :\n";
                                if(true){
                                    mess+="    no rooms to create a room send 'new'\n";
                                }
                                for(int i=53001;i<nextPort;i+=2){
                                    mess+="    "+ std::to_string(i)+"\n";
                                }
                                responsePacket<<mess;
                                client.send(responsePacket);
                            }
                            else if (std::stoi(message)>53000 && std::stoi(message)<nextPort) {
                                std::string reply = "Message received!";
                                sf::Packet responsePacket;
                                std::string mess='0'+message;
                                responsePacket << mess;
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
}