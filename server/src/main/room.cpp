#include "room.h"

Room::Room(std::string _roomName){
  roomName = _roomName;
}

/**
 * Agrega el socket de un cliente nuevo a la lista y lo marca como false (no
 * unido).
 * @param clientSocket el socket del cliente que se invitó al cuarto.
 */
void Room::inviteUser(int clientSocket){
  if(!isUserInList(clientSocket)){
    clientMap.insert({clientSocket, false});
  }
}

/**
 * Se marca un cliente que está en la lista como unido.
 * @param clientSocket el socket del cliente que se marcó como unido.
 * @throw NoSuchUserInRoomException si el usuario no está en la lista.
 */
void Room::setUserToJoined(int clientSocket){
  if(!isUserInList(clientSocket)){
    throw NoSuchUserInRoomException("");
  }
  clientMap[clientSocket] = true;
}

/**
 * Se borra un cliente del mapa de sockets de clientes.
 * @param clientSocket el socket del cliente que se borrará del mapa.
 * @throw NoSuchUserInRoomException si el usuario no está en la lista.
 */
void Room::eraseUser(int clientSocket){
  if(!isUserInList(clientSocket)){
    throw NoSuchUserInRoomException("");
  }
  clientMap.erase(clientSocket);
}

/**
 * La función regresa true si el usuario está en la lista y false en otro caso.
 * @param clientSocket el socket del cliente que verificaremos si está en la
 * lista.
 * @return El valor booleano que describe si el socket de un cliente está en el
 * mapa de sockets.
 */
bool Room::isUserInList(int clientSocket){
  return clientMap.find(clientSocket) != clientMap.end();
}

/**
 * Si el usuario está en la lista y ya se encuentra unido regresa true, si aún
 * no se une regresa false.
 * @param clientSocket el socket del cliente que verificaremos si está unido.
 * @return el valor booleano del estado de un cliente en el cuarto.
 * @throw NoSuchUserInRoomException si el usuario aún no está unido.
 */
bool Room::isUserJoined(int clientSocket){
  if(clientMap.find(clientSocket) != clientMap.end()){
    return clientMap.at(clientSocket);
  }

  throw NoSuchUserInRoomException("");
}

/**
 * Regresa un vector de sockets de clientes que ya se encuentran unidos al
 * cuarto.
 * @return joinedClients el vector de clientes unidos.
 */
std::vector<int> Room::getJoinedClients(){
  std::vector<int> joinedClients;
  for(const auto& pair : clientMap){
    if(pair.second){
      joinedClients.push_back(pair.first);
    }
  }
  return joinedClients;
}
