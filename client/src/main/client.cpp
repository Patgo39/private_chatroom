#include "client.h"

Client::Client(int _port, int _bufferSize, std::string _ipAddress){
  port = _port;
  bufferSize = bufferSize;
  ipAddress = _ipAddress;
  clientSocket = 0;
}

void Client::start(){
    struct sockaddr_in serv_addr;
    
    // Se crea un socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        throw ClientConnectionException("Socket creation error");
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    
    // Convierte IPv4 y IPv6 de texto a binario.
    if (inet_pton(AF_INET, ipAddress.c_str(), &serv_addr.sin_addr) <= 0) {
        throw ClientConnectionException("Invalid address/ Address not supported");
    }
    // Se conecta al sevidor
    if (connect(clientSocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        throw ClientConnectionException("Connection Failed");
    }
}

void Client::sendMessage(std::string message){
  send(clientSocket, message.c_str(), message.size(), 0);
}

std::string Client::receiveMessages(){
  char buffer[bufferSize] = {0};
  ssize_t valread = read(clientSocket, buffer, bufferSize);
  return buffer;
}

void Client::closeConection(){
  close(clientSocket);
}
