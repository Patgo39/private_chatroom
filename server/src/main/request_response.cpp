#include "request_response.h"

RequestResponse::RequestResponse(){
  keepConection = true;
  userResponse = "";
  message = {"", "", {}, Message::MessageType::NONMESSAGE};
}

Message RequestResponse::getPublicMessage(){
  return message;
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

void RequestResponse::setGeneralMessage(std::string json){
  message = {json, "", {}, Message::MessageType::GENERAL};
  
}

void RequestResponse::setSpecificMessage(std::string json, std::vector<int> sockets){
  message = {json, "", sockets, Message::MessageType::SPECIFIC};
}

