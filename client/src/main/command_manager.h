#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <iostream>
#include <string>
#include <json/json.h>
#include <vector>
#include <sstream>
#include "command_exception.cpp"
#include "command_result.h"

class CommandManager{
  CommandResult cmdRes;
 public:
  CommandManager();
  // Se construye un json dado el comando recibido.
  CommandResult getJsonFromCommand(std::string userMessage);

 private:
  // Se obtienen los parámetros del comando en un vector.
  std::vector<std::string> getCommandAsVector(std::string userMessage);
  // Se construye el json para el comando /identify.
  std::string manageIdentification(std::vector<std::string> command);
  // Se muestra al usuario la lista de comandos.
  std::string manageHelpCommand();
  // Se construye el json para el comando /changestatus.
  std::string manageNewStatus(std::vector<std::string> command);
  // Se construye el json para el comando /list.
  std::string manageUsersList(std::vector<std::string> command);
  // Se construye el json para el comando /private.
  std::string managePrivateMessage(std::vector<std::string> command);
  // Se construye el json para el comando /newroom.
  std::string manageNewRoom(std::vector<std::string> command);
  // Se construye el json para el comando /invite
  std::string manageInviteUsersToRoom(std::vector<std::string> command);
  // Se construye el json para el comando /join.
  std::string manageJoinRoom(std::vector<std::string> command);
  // Se construye el json para el comando /roomlist.
  std::string manageRoomList(std::vector<std::string> command);
  // Se construye el json para el comando /leave.
  std::string manageLeaveRoom(std::vector<std::string> command);
  // Se construye el json para el comando /disconnect.
  std::string manageDisconnect();
  // Se construye el json para un texto nomal.
  std::string manageNormalText(std::string userMessage);
  // Convierte un objeto json a cadena.
  std::string turnJsonToString(Json::Value json);
  // Agrega los parámetros de un comando a un vector.
  std::vector<std::string> getParametersFromCommand(std::vector<std::string> command);
};

#endif
