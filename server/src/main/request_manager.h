#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <json/json.h>
#include "client.h"
#include "json_controller.h"
#include "request_response.h"
#include "user_status.h"

class RequestManager{
  /**
   * La estructura ServerData contiene referencias a los atributos del servidor
   * con el fin de modificarlos u obtener datos específicos acorde cada
   * petición del cliente.
   **/
  struct ServerData{
    Client &requester;
    std::map<int,Client> &socketsMap;
    std::map<std::string, Room> &roomMap;

    ServerData(Client &_requester, std::map<int,Client> &_socketsMap, std::map<std::string, Room> &_roomMap) : requester(_requester), socketsMap(_socketsMap), roomMap(_roomMap){}
  };

  // Objecto para crear los json de respuesta y aviso para el o los clientes.
  JsonController jsonController;
public:
  RequestManager();
  // Regresa un objeto RequestResponse para cada tipo de petición.
  RequestResponse getResponse(Client &requester, std::string request, std::map<int, Client> &socketsMap, std::map<std::string, Room> &roomMap);
private:
  // Administra la petición de identificación.
  RequestResponse manageIdentifyRequest(Json::Value value, ServerData data);
  // Administra la petición de cambio de estado.
  RequestResponse manageStatusRequest(Json::Value value, ServerData data);
  // Administra la solicitud de la lista de usuarios.
  RequestResponse manageUsersRequest(ServerData data);
  // Administra la petición de mensaje privado.
  RequestResponse manageTextRequest(Json::Value value, ServerData data);
  // Administra la petición de un texto público.
  RequestResponse managePublicTextRequest(Json::Value value, ServerData data);
  // Crea un cuarto con el nombre que especifique el usuario.
  RequestResponse manageNewRoomRequest(Json::Value value, ServerData data);
  // Invita a uno o varios usuarios a un cuarto.
  RequestResponse manageInviteRequest(Json::Value value, ServerData data);
  // Administra la petición de union a un cuarto.
  RequestResponse manageJoinRoomRequest(Json::Value value, ServerData data);
  // Administra la solicitud de la lista de usuarios en un cuarto.
  RequestResponse manageRoomUsersRequest(Json::Value value, ServerData data);
  // Adminsitra la petición de un mensaje a un cuarto.
  RequestResponse manageRoomTextRequest(Json::Value value, ServerData data);
  // Administra la solicitud de abandono de un cuarto.
  RequestResponse manageLeaveRoomRequest(Json::Value value, ServerData data);
  // Maneja el caso cuando el usuario se desconecta del chat.
  RequestResponse manageDisconnectRequest(ServerData data);
  // Regresa el objeto respuesta para Jsons incompletos o invalidos.
  RequestResponse getInvalidRequestResponse(ServerData data);
  // Elimina los espacios al inicio y final de un string.
  std::string trim(const std::string& str);
};

#endif
