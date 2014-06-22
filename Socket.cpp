#include <iostream>
#include "Socket.hpp"

Socket::Socket(char s){
    port = 53000;
    is_server = (s == 'S');
}

bool Socket::connect(){
    if(not is_server){
        //Connect the socket
        sf::Socket::Status status = socket.connect("127.0.0.1", port);
        if (status != sf::Socket::Done)	{
          //  std::cout << "Socket NOT conected" << std::endl;
            return false;
        }
        //else std::cout << "Socket Conected" << port << std::endl;
    }
    else {
        //Bind the listener to a port
        if (listener.listen(port) != sf::Socket::Done) {
        //    std::cout << "Socket Not listened" << std::endl;
            return false;
        }
        //else std::cout << "Im Listening the port " << port << std::endl;
        // Accept the connection
        if (listener.accept(client) != sf::Socket::Done) {
         //   std::cout << "Client NOT Accepted" << std::endl;
            return false;
        }
        //else std::cout << "Conection Accepted" << std::endl;
    }
    return true;
}

bool Socket::send(char data[], size_t size, int p){
    // TCP socket:
    if(p == 0){
        if (client.send(data, size) != sf::Socket::Done) {
            return false;
        }
        else { 
           // std::cout << "Sent!  ->" << int(data[0])<< std::endl;
            return true;
        }
    }
    else {

        if (socket.send(data, size) != sf::Socket::Done) {
            return false;
        }
        else {
           // std::cout << "Sent!" << std::endl;
            return true;
        }
    }
}

bool Socket::recieve(char data[], size_t size, int p){

    std::size_t received;
    if(p == 0){
        
        if (client.receive(data, size, received) != sf::Socket::Done)	{
            return false;
        }
        else {
          //  std::cout << "Recieved!" << std::endl;
            return true;
        }
    }
    else{
        if (socket.receive(data, size, received) != sf::Socket::Done)  {
            return false;
        }
        else {
           // std::cout << "Recieved! " << int(data[0]) << " "<< received <<std::endl;
            return true;
        }
    }
}
