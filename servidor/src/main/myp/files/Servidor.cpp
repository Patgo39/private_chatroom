#include "Servidor.h"

Servidor::Servidor(){
  std::cout<<"Escriba el número del puerto: ";
  std::cin>>puerto;
}
/**
 * Inicia todo el funcionamiento del servidor desde crear un socket hasta
 * lidiar con multiples clientes y recibir y procesar sus solicitudes.
 */
void Servidor::inicia(){
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  lanzaError("\nError estableciendo la conexión.", "\nConexión del servidor establecida.", serverSocket, true);
  
  vincula();
  conectaClientes();
  desconecta();
}

/**
 * Vincula el socket del servidor definiendo la dirección y teniendo en cuenta
 * el puerto.
 * Lanza un error si no se logra vincular el socket.
 */
void Servidor::vincula(){
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(puerto);
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  
  conexion = bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  
  lanzaError("Error al vincular el socket.", "Vinculación del servidor establecida.", conexion, true);
}

/**
 * Comienza a esuchcar las peticiones de conexión de parte de los clientes y
 * entra a un bucle para aceptar todas las solicitudes que reciba.
 * dentro del bucle identifica al usuario conectado y en caso de no haber un
 * error, el servidor lo agrega al mapa de clientes y dispara un hilo de
 * ejecución para manejar la comunicación con el cliente.
 * En caso de error, el servidor ignora al cliente y termina con la vuelta del
 * ciclo.
 */
void Servidor::conectaClientes(){
  
  listen(serverSocket, 10);
  int clientSocket;
  sockaddr_in clientAddr;
  socklen_t clientAddrLen;
  
  while(true){
    
    clientAddrLen= sizeof(clientAddr);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);

    lanzaError("Error al aceptar al cliente.", "Conexión con el cliente establecida.", clientSocket, true);
    
    if(!identificarUsuario(clientSocket)) continue;
      
    std::thread tclient(&Servidor::manejaCliente, this, clientSocket);
    tclient.detach();
  }

  desconecta();
}

/**
 * Recibe y procesa las peticiones del cliente.
 * 
 * @param clientSocket el socket del cliente.
 */
void Servidor::manejaCliente(int clientSocket){
  std::string buffer;
  Usuario us = mapa[clientSocket];
  
  while(true){
    
    buffer = recibeMensaje(clientSocket);

    manejaPeticion(buffer, clientSocket);
    
    buffer.clear();
    
  }
}

/**
 * El método es llamado cuando el usuario solicitó desconectarse.
 * Se borra al usuario del mapa de clientes y avisa a los demás usuarios que
 * se desconectó.
 * 
 * @param clientSocket el socket del cliente.
 */
void Servidor::desconectaUsuario(int clientSocket){
  Usuario us = mapa[clientSocket];
  mapa.erase(clientSocket);
  //close(clientSocket);
  std::cout<<us.getNombre()<<" se desconectó."<<std::endl;
  if(mapa.size() == 0){
    desconecta();
  }
}

/**
 * Desconecta el socket del servidor para terminar con el programa.
 */
void Servidor::desconecta(){
  close(serverSocket);
  std::cout<<"\nServidor desconectado"<<std::endl;
}

void Servidor::lanzaError(std::string mensaje1, std::string mensaje2, int valor, bool termina){
  if(valor < 0){
    std::cout<<mensaje1<<std::endl;
    if(termina){
      desconecta();
      exit(1);
    }
  }
  
  std::cout<<mensaje2<<std::endl;
}

/**
 * Manda un mensaje a todos los usuarios, menos al que envió dicho mensaje.
 *
 * @param clientSocket. El socket del usuario que envió el mensaje. 
 * @param mensaje. El mensaje que se enviará a los demás usuarios.
 */
void Servidor::mandaMensajeGeneral(int clientSocket, std::string mensaje){
  mtx.lock();
  
  for(auto& elemento:mapa){
    if(elemento.first != clientSocket){
      send(elemento.first, mensaje.c_str(), mensaje.length(), 0);
    }
  }
  mtx.unlock();
}

/**
 * Envía un mensaje especificamente al usuario que es especificado.
 *
 * @param clientSocket el socket del cliente.
 * @param mensaje el mensaje que se enviará al cliente.
 */
void Servidor::mandaMensajeIndividual(int clientSocket, std::string mensaje){
  send(clientSocket, mensaje.c_str(), mensaje.length(), 0);
}

std::string Servidor::recibeMensaje(int clientSocket){
  char buffer[512] = {};
  recv(clientSocket, buffer, sizeof(buffer), 0);
  return std::string(buffer);
}

/**
 * Maneja la petición del usuario. Se contempla cada caso posible y regresa una
 * cadena del Json de la respuesta del servidor para la solicitud.
 * 
 * @param solicitud la cadena del Json de la solicitud del usuario.
 * @param clientSocket el socket del cliente.
 * @return respuesta la respuesta a la solicitud del usuario.
 */
void Servidor::manejaPeticion(std::string solicitud, int clientSocket){
  int tipoCliente = ManejaPeticionCliente::manejaPeticion(solicitud);
  std::string respuesta;
  bool valido;
  switch(tipoCliente){
  case TipoCliente::Tipo::STATUS:
    
    {
      valido = true;
      respuesta = ManejaPeticionCliente::manejaCambioEstado(solicitud, clientSocket, mapa, valido);
      
      if(valido){
	mandaMensajeGeneral(clientSocket, respuesta);
      }else{
	mandaMensajeIndividual(clientSocket, respuesta);
	respuesta = ManejaPeticionCliente::manejaDesconexion(mapa[clientSocket].getNombre());
	mtx.lock();
	desconectaUsuario(clientSocket);
	mtx.unlock();
	mandaMensajeGeneral(clientSocket, respuesta);
      }
    }
    break;
    
  case TipoCliente::Tipo::USERS:
    
    respuesta = ManejaPeticionCliente::manejaListaGeneral(mapa);
    mandaMensajeIndividual(clientSocket, respuesta);
    break;
    
  case TipoCliente::Tipo::TEXT:
    {
      int socketDestinatario = -1;
      respuesta = ManejaPeticionCliente::manejaMensajePrivado(solicitud, mapa, clientSocket, socketDestinatario);
      
      if(socketDestinatario == -1){
	mandaMensajeIndividual(clientSocket, respuesta);
      }else{
	mandaMensajeIndividual(socketDestinatario, respuesta);
      }
    }
    break;
  case TipoCliente::Tipo::PUBLIC_TEXT:
    
    respuesta = ManejaPeticionCliente::manejaTextoPublico(solicitud, mapa[clientSocket].getNombre());
    mandaMensajeGeneral(clientSocket, respuesta);
    break;
    
  case TipoCliente::Tipo::NEW_ROOM:
    {
      Cuarto cuarto;
      respuesta = ManejaPeticionCliente::manejaNuevoCuarto(solicitud, cuarto, cuartos);
      mandaMensajeIndividual(clientSocket, respuesta);
    }
    break;
  case TipoCliente::Tipo::INVITE:
    {
      std::vector<int> clientesAInvitar;
      valido = true;
      respuesta = ManejaPeticionCliente::manejaInvitacion(solicitud, cuartos, valido, mapa, clientesAInvitar, clientSocket);
      if(!valido){
	mandaMensajeIndividual(clientSocket, respuesta);
      }else{
	for(int socket:clientesAInvitar){
	  mandaMensajeIndividual(socket, respuesta);
	}
      }
    }
    break;
  case TipoCliente::Tipo::JOIN_ROOM:
    {
      std::string avisoDeUsuarioConectado;
      valido = true;
      respuesta = ManejaPeticionCliente::manejaUnionACuarto(solicitud, avisoDeUsuarioConectado, cuartos, valido, mapa[clientSocket].getNombre());
    }
    break;
  case TipoCliente::Tipo::ROOM_USERS:
    break;
  case TipoCliente::Tipo::ROOM_TEXT:
    break;
  case TipoCliente::Tipo::LEAVE_ROOM:
    break;
  case TipoCliente::Tipo::DISCONNECT:
    respuesta = ManejaPeticionCliente::manejaDesconexion(mapa[clientSocket].getNombre());
    mtx.lock();
    desconectaUsuario(clientSocket);
    mtx.unlock();
    mandaMensajeGeneral(clientSocket, respuesta);
    break;
  }
}

/**
 * Identifica al usuario
 */
bool Servidor::identificarUsuario(int clientSocket){
  std::string buff;
  std::string nombre;
  bool valido = true;
  std::string notificacion;
  buff = recibeMensaje(clientSocket);
    
  std::string respuesta = ManejaPeticionCliente::manejaIdentificacion(buff, mapa, valido, nombre, notificacion);
  
  mandaMensajeIndividual(clientSocket, respuesta);
  if(!valido) return false;
  mandaMensajeGeneral(clientSocket, notificacion);
  
  mtx.lock();
  Usuario us(nombre, clientSocket);
  mapa[clientSocket] = us;
  mtx.unlock();
  
  return true;
}
