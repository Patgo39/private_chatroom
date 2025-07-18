#include "server.h"

std::mutex mtx; // Objeto para evitar que múltiples hilos accedan a recursos compartidos.

/**
 * El constructor del servidor inicializa el puerto y el tamaño del buffer con
 * aquellos datos que recibe. Además el socket del servidor inicia en 0.
 * @param _port el puerto por el que se conectarán los clientes.
 * @param _bufferSize el tamaño máximo del buffer del servidor
 */
Server::Server(int _port, int _bufferSize){
  port = _port;
  bufferSize = _bufferSize;
  serverSocket = 0;
}

/**
 * Se crea e inicia el hilo principal del servidor el cual acepta clientes e
 * instantáneamente crea un hilo aparte para cada uno.
 */
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

/**
 * La función se ejecuta en un hilo de ejecución que solo se detendrá si el
 * cliente ejecuta el comando para desconectarse u ocurre un error de
 * compatibilidad con algún comando.
 * Se administran las peticiones del cliente en base a los comandos que
 * introduce.
 * @param clientSocket el socket por el cual el cliente se comunica con el
 * servidor.
 */
void Server::manageClient(int clientSocket){

  mtx.lock();
  //Se agrega el cliente y el socket al mapa, siendo el socket la llave.
  socketsMap.insert({clientSocket, Client(clientSocket)});
  mtx.unlock();
  
  bool keepConection = true;
  std::cout<<"Client "<<clientSocket<<" connected succesfully!"<<std::endl;
  char buffer[bufferSize] = {0};

  RequestManager manager = RequestManager();
  
  while(keepConection){

    int received = recv(clientSocket, buffer, bufferSize, 0);

    if(received <= 0) continue;

    //Se conserva unicamente la cantidad de bytes leídos en el buffer.
    buffer[received] = '\0';
    std::string message(buffer); // Se convierte el char array a string
    std::cout<<"client "<<clientSocket<<": "<<message<<std::endl; // Se imprime el mensaje del usuario

    mtx.lock();
    RequestResponse response = manager.getResponse(socketsMap.at(clientSocket), message, socketsMap, roomMap);
    mtx.unlock();

    // Se actualiza el estado de la conexión; si debe continuar o no.
    keepConection = response.getKeepConection();

    manageClientRequest(socketsMap.at(clientSocket), response);
    
    //Se eliminan los datos del buffer y data.
    buffer[0] = '\0';
    message.clear();
  }

  disconnectClient(clientSocket); // Se desconecta al usuario
}

/**
 * En base a la petición del cliente, se ejecutan los cambios correspondientes
 * en los atributos del servidor y en objetos como el mapa de clientes o el
 * mapa de cuartos.
 * Se manda un mensaje de respuesta al cliente u otros clientes.
 * @param client el cliente que realizó la petición.
 * @param response el objeto respuesta que contiene los detalles de la respuesta
 * para el usuario.
 */
void Server:: manageClientRequest(Client client, RequestResponse response){
  std::string clientResponse = response.getUserResponse();
  int requesterSocket = client.getSocket();
  std::vector<Message> messageVector = response.getMessageVector(); // Se obtiene el mensaje publico para todos a algunos usuarios en especifico.
  
  if(clientResponse != ""){
    sendMessageToClient(client.getSocket(), clientResponse);
    std::cout<<"Client Message: "<<clientResponse<<std::endl;
  }

  for(Message messageAdvice : messageVector){
    switch(messageAdvice.type){
      // Caso de mandar un mensaje a todos los clientes conectados.
    case Message::MessageType::GENERAL://General
      {
	for(const auto& pair : socketsMap){
	  int socket = pair.first;
	  Client c = pair.second;
	  
	// No se envia el mensaje al cliente que emitió la petición.
	  if(socket == requesterSocket || !c.isIdentified()){
	    continue;
	}
	  sendMessageToClient(socket, messageAdvice.message);
	  std::cout<<"General Message: "<<messageAdvice.message<<std::endl;
	}
    }
      break;
      
    case Message::MessageType::SPECIFIC: //Specific
      {
	std::vector<int> targets = messageAdvice.targetSockets; // Se obtiene el vector de los clientes a mandar el mensaje.
	for(int sock : targets){
	  sendMessageToClient(sock, messageAdvice.message); 
	}
      }
      break;
      
    default:
      std::cout<<"Message Type Format is invalid"<<std::endl;
    }
  }
}

/**
 * Manda un mensaje a un cliente en especifico dado su socket.
 * @param clientSocket el socket del cliente que recibirá el mensaje.
 * @param data la cadena que contiene el mensaje para el cliente.
 */
void Server::sendMessageToClient(int clientSocket, std::string data){
  send(clientSocket, data.c_str(), data.length(), 0);

}

/**
 * Desconecta a un cliente dado su socket.
 * @param clientSocket el socket del cliente.
 */
void Server::disconnectClient(int clientSocket){
  mtx.lock();
  socketsMap.erase(clientSocket); // Se elimina el cliente del mapa de sockets.
  mtx.unlock();
  close(clientSocket);
}

/**
 * Cierra el socket del servidor evitando que más clientes puedan conectarse.
 */
void Server::closeConnection(){
  close(serverSocket);
}
