#include "Cliente.h"

Cliente::Cliente(){
  std::cout<<"Escriba el número del puerto: ";
  std::cin>>puerto;
  
  std::cout<<"\nEscriba su nombre: ";
  std::cin>>nombre;
  if(nombre.length() > 8){
    std::cout<<"El nombre no debe tener más de 8 caracteres."<<std::endl;
    exit(1);
  }
}

void Cliente::inicia(){
  //Se crea el socket.
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  
  if(clientSocket < 0){
    std::cout<<"\nError estableciendo la conexión."<<std::endl;
    desconecta(clientSocket);
    exit(1);
  }
  
  conecta(clientSocket);
  desconecta(clientSocket);
}


void Cliente::conecta(int clientSocket){
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(puerto);
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  
  conexion = connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

  if(conexion < 0){
    std::cout<<"No se pudo conectar al servidor."<<std::endl;
    desconecta(clientSocket);
    exit(1);
  }


  std::string identificador = MensajeJson::peticionIdentificaUsuario(nombre);
  send(clientSocket, identificador.c_str(), identificador.length() + 1, 0);
  
  char buff[512] = {};
  recv(clientSocket, buff, sizeof(buff), 0);
  
  if((MensajeJson::manejaRespuestaServidor(buff)) < 0){
    desconecta(clientSocket);
    exit(1);
  }

  
  std::thread t1(&Cliente::mandaMensaje, this, clientSocket);
  std::thread t2(&Cliente::recibeMensaje, this, clientSocket);

  t1.join();
  t2.join();
}

void Cliente::mandaMensaje(int clientSocket){
  
  while(true){
    char buffer[512];
    std::cout<<"Tú: ";
    std::cin>>std::ws;
    std::cin.getline(buffer, 512, '\n');
    
    
    if(strcmp(buffer, "EXIT") == 0){
      send(clientSocket, &buffer, sizeof(buffer), 0);
      desconecta(clientSocket);
      exit(1);
    }
    
    std::string mensaje;
    mensaje = MensajeJson::manejaMensajeCliente(buffer);
    send(clientSocket, mensaje.c_str(), mensaje.length(), 0);
  }
}

void Cliente::recibeMensaje(int clientSocket){
  while(true){
    
    char buff[512];

    int recibido = recv(clientSocket, buff, sizeof(buff), 0);
    if(recibido <= 0)
      continue;

    buff[recibido] = '\0';
    std::cout<<"\r"<<std::string(50, ' ')<<"\r";
    
    if(MensajeJson::manejaRespuestaServidor(buff) == 0){
      MensajeJson::manejaAvisoServidor(buff);
    }
    
    std::cout<<"Tú: ";
    std::fflush(stdout);
    
  }
}

void Cliente::desconecta(int clientSocket){
  close(clientSocket);
}


