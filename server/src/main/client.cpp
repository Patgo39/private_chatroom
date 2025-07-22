#include <client.h>

Client::Client(int _clientSocket){
  clientSocket = _clientSocket;
  identified = false;
  userName = "";
  status = UserStatus::Status::ACTIVE;
}

/**
 * Establece el nombre de usuario del cliente al que la función recibió.
 * @param _userName el nombre de usuario que se establecerá para el cliente.
 */
void Client::setUserName(std::string _userName){
  if(userName == ""){
    userName = _userName;
  }
}

/**
 * Actualzia el etsado del usuario al recibido por la función.
 * @param _status el estado al que se actualizará el del cliente.
 */
void Client::setUserStatus(UserStatus::Status _status){
  status = _status;
}

/**
 * Regresa el nombre del usuario del cliente.
 * @return el nombre de usuario del cliente.
 */
std::string Client::getUserName(){
  return userName;
}

/**
 * Regresa el estado del cliente.
 * @return status el estado del cliente.
 */
std::string Client::getUserStatus(){
  return UserStatus::getString(status);
}

/**
 * Actualiza al cliente como identificado.
 */
void Client::identify(){
  identified = true;
}

/**
 * Regresa el socket del cliente.
 * @return clientSocket el socket del cliente.
 */
int Client::getSocket(){
  return clientSocket;
}

/**
 * Regresa true si el cliente se identificó, false en otro caso.
 * @return identified el estado de identificación del usuario.
 */
bool Client::isIdentified(){
  return identified;
}

/**
 * Agrega el nombre de un cuarto al que el cliente se unió, al vector de
 * cuartos.
 * @param roomName el nombre del cuarto al que el cliente se unió.
 */
void Client::joinToRoom(std::string roomName){
  rooms.push_back(roomName);
}

/**
 * Elimina el nombre de un cuarto del vector de cuartos.
 * @param roomName el nombre del cuarto a eliminar.
 */
void Client::forgetRoom(std::string roomName){
  int position = 0;
  for(std::string name:rooms){
    if(name == roomName){
      rooms.erase(rooms.begin() + position);
      break;
    }
    position ++;
  }
  
}

/**
 * Regresa el vector de cuartos a los que el cliente se ha unido.
 * @return rooms el vector de cuartos.
 */
std::vector<std::string> Client::getRoomVector(){
  return rooms;
}


