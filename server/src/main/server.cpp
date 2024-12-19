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
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    // Forcefully attaching socket to the port 8080
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Bind the socket to the network address and port
    if (bind(serverSocket, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    // Start listening for incoming connections
    if (listen(serverSocket, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Accept incoming connection
    if ((clientSocket = accept(serverSocket, (struct sockaddr*)&address, &addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
}

void Server::closeConnection(){
  close(serverSocket);
}
