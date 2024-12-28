#include "server.h"

Server::Server(int _port, int _bufferSize){
  port = _port;
  bufferSize = _bufferSize;
  serverSocket = 0;
}

void Server::start(){
  struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    
    // Creando un socket.
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    // Se relaciona el socket al puerto
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(1);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    
    // Se vincula el socket a la dirección de la red y al puerto.
    if (bind(serverSocket, (struct sockaddr*)&address, sizeof(address)) < 0) {
      perror("bind failed");
      exit(1);
    }
    // Escucha las posibles conexiones.
    if (listen(serverSocket, 3) < 0) {
      perror("listen");
      exit(1);
    }
    std::cout<<"Server started succesfully!"<<std::endl;
    // Accepta nuevas conexiones.
    while(true){
      //Socket para un nuevo cliente.
      int clientSocket;
      
      if ((clientSocket = accept(serverSocket, (struct sockaddr*)&address, &addrlen)) < 0) {
        perror("accept");
        exit(1);
      }else{
	std::thread threadClient(&Server::manageClient, this, clientSocket);
	threadClient.detach();
      }
    }
    
}

void Server::manageClient(int clientSocket){
  
  clientSocketsArray.push_back(clientSocket);
  std::cout<<"CLient "<<clientSocket<<" connected succesfully!"<<std::endl;
  char buffer[bufferSize] = {0};
  
  while(true){

    int received = recv(clientSocket, buffer, bufferSize, 0);

    if(received <= 0) continue;

    //Se conserva unicamente la cantidad de bytes leídos en el buffer.
    buffer[received] = '\0';
    std::string data(buffer);
    
    std::cout<<"server: "<<buffer<<std::endl;
    
    for(int socket : clientSocketsArray){
      sendMessageToClient(socket, data);
    }

    //Se eliminan los datos del buffer y data.
    buffer[0] = '\0';
    data.clear();
  }
}

void Server::sendMessageToClient(int clientSocket, std::string data){
  send(clientSocket, data.c_str(), data.length(), 0);
}

void Server::closeConnection(){
  close(serverSocket);
}
