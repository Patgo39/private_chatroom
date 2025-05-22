#include "request_manager.h"

RequestManager::RequestManager(){}

void RequestManager::getResponse(Client requester, std::string request){

  
  Json::CharReaderBuilder builder;
  builder["collectComments"] = false;
  Json::Value value;
  std::string errs;
  std::istringstream streamRequest(request);
  bool ok = parseFromStream(builder, streamRequest, &value, &errs);

  if(!ok){
    std::cout<<"ERRRRRRRRRRRRRRRRROOOOOOOOOR"<<std::endl;
  }

  
  
}
