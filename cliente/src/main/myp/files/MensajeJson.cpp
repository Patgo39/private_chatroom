#include "MensajeJson.h"

void MensajeJson::manejaMensajeCliente(char buffer[]){
  std::vector<std::string> buff = convierteAVector(buffer);

  if(buff[0] == "request"){
    
  }
}

void MensajeJson::manejaMensajeServidor(char buffer[]){
  Json::Value buff = convierteAJson(buffer);
}

Json::Value MensajeJson::convierteAJson(char buffer[]){
  Json::Value bufferJson;
  Json::CharReaderBuilder builder;
  JSONCPP_STRING errs;
  std::istringstream s(buffer);

  parseFromStream(builder, s, &bufferJson, &errs);

  return bufferJson;
}

std::string MensajeJson::convierteACadena(Json::Value objetoJson){
  Json::StreamWriterBuilder builder;
  const std::string output = Json::writeString(builder, objetoJson);

  return output;
}

std::vector<std::string> MensajeJson::convierteAVector(char buffer[]){
  std::string cadena(buffer);
  std::vector<std::string> vec;
  std::string temp;
  std::stringstream ss(cadena);

  while(getline(ss, temp, ' ')){
    vec.push_back(temp);
  }
  return vec;
}


