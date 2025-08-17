#include "client.h"

Client::Client(int _port, int _bufferSize, std::string _ipAddress){
  port = _port;
  bufferSize = _bufferSize;
  ipAddress = _ipAddress;
  clientSocket = 0;
  buffer_string = "";
  stop_listening = false;
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

    listening_thread = std::thread(&Client::onServerMessageEvent, this);
}

void Client::sendMessage(std::string message){
  send(clientSocket, message.c_str(), message.length(), 0);
}

std::string Client::receiveMessages(){
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this] {return stop_listening || !buffer_string.empty();});

  if(stop_listening)
    return "";

  std::string aux_string = buffer_string;
  buffer_string.clear();
  return aux_string;
}

void Client::onServerMessageEvent(){
  char buffer[bufferSize] = {0};
  while(!stop_listening){
    ssize_t bytes_received = recv(clientSocket, buffer, bufferSize, 0);
    if(bytes_received > 0){
      buffer[bytes_received] = '\0';
      {
	std::lock_guard<std::mutex> lock(mtx);
	buffer_string = buffer;
      }
      cv.notify_one();
    }else{
      continue;
    }
  }
}

void Client::closeConnection(){
  {
    std::lock_guard<std::mutex> lock(mtx);
    stop_listening = true;
  }
  shutdown(clientSocket, SHUT_RDWR);
  close(clientSocket);
  cv.notify_all();
  if(listening_thread.joinable()) {
    listening_thread.join();
  }
}
