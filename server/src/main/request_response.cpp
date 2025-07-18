#include "request_response.h"

RequestResponse::RequestResponse(){
  keepConection = true;
  userResponse = "";
}

std::string RequestResponse::getUserResponse(){
  return userResponse;
}

bool RequestResponse::getKeepConection(){
  return keepConection;
}



void RequestResponse::stopConection(){
  keepConection = false;
}

void RequestResponse::setUserResponse(std::string response){
  userResponse = response;
}

void RequestResponse::pushGeneralMessage(std::string json){
  messageVector.push_back({json, {}, Message::MessageType::GENERAL});
  
}

void RequestResponse::pushSpecificMessage(std::string json, std::vector<int> sockets){
  messageVector.push_back({json, sockets, Message::MessageType::SPECIFIC});
}

std::vector<Message> RequestResponse::getMessageVector(){
  return messageVector;
}
