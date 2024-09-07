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
  
  lanzaError("\nError estableciendo la conexión.", "\nConexión del cliente establecida.", clientSocket, true, clientSocket);
  
  conecta(clientSocket);
  desconecta(clientSocket);
}


void Cliente::conecta(int clientSocket){
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(puerto);
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  
  conexion = connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  
  lanzaError("No se pudo conectar al servidor.", "Conexión con el servidor establecida.", conexion, true, clientSocket);


  std::string identificador = MensajeJson::identificaUsuario(nombre);
  std::cout<<identificador<<std::endl;
  send(clientSocket, identificador.c_str(), identificador.length() + 1, 0);
  
  char buff[512] = {};
  recv(clientSocket, buff, sizeof(buff), 0);
  std::cout<<buff<<std::endl;
  
  if((MensajeJson::manejaRespuestaServidor(buff)) < 0){
    std::cout<<"Ese nombre ya está usado."<<std::endl;
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
    send(clientSocket, &buffer, sizeof(buffer), 0);
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
    std::cout<<buff<<std::endl;
    
    std::cout<<"Tú: ";
    std::fflush(stdout);
    
  }
}

void Cliente::desconecta(int clientSocket){
  close(clientSocket);
}

void Cliente::lanzaError(std::string mensaje1, std::string mensaje2, int valor, bool termina, int clientSocket){
  if(valor < 0){
    std::cout<<mensaje1<<std::endl;
    if(termina){
      desconecta(clientSocket);
      exit(1);
    }
  }
  
  std::cout<<mensaje2<<std::endl;
}
