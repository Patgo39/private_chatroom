#include "room.h"

Room::Room(std::string _roomName){
  roomName = _roomName;
}

void Room::inviteUser(int clientSocket){
  if(!isUserInList(clientSocket)){
    clientMap[clientSocket] = false;
    clientMap.insert({clientSocket, false});
  }
}

void Room::setUserToJoined(int clientSocket){
  if(isUserInList(clientSocket)){
    clientMap[clientSocket] = true;
  }
  throw NoSuchUserInRoomException("");
}

void Room::eraseUser(int clientSocket){
  if(isUserInList(clientSocket)){
    clientMap.erase(clientSocket);
  }
  throw NoSuchUserInRoomException("");
}

bool Room::isUserInList(int clientSocket){
  return clientMap.find(clientSocket) != clientMap.end();
}

bool Room::isUserJoined(int clientSocket){
  if(clientMap.find(clientSocket) != clientMap.end()){
    return clientMap.at(clientSocket);
  }

  throw NoSuchUserInRoomException("");
}

std::vector<int> Room::getJoinedClients(){
  std::vector<int> joinedClients;
  for(const auto& pair : clientMap){
    if(pair.second){
      joinedClients.push_back(pair.first);
    }
  }
  return joinedClients;
}
