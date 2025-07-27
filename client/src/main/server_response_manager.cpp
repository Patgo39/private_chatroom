#include "server_response_manager.h"

ServerResponseManager::ServerResponseManager(){}

Message ServerResponseManager::getMessageFromResponse(std::string serverResponse){
  Json::CharReaderBuider builder;
  builder["collectComments"] = false;
  Json::Value value;
  std::string errs;
  std::istringstream streamRequest(request);
  bool ok = parseFromStream(builder, streamRequest, &value, &errs);

  if(!ok){
    /**Lanza excepción o algo por el estilo por no ser un json*/
  }

  if(!value.isMember("type")){
    /**Lanza excepción o algo por el estilo por no tener la llave necesaria*/
  }
}
