#include "MensajeJson.h"

std::string MensajeJson::identificaUsuario(std::string nombre){
  Json::Value identificador;
  identificador["type"] = TipoCliente::getString(TipoCliente::Tipo::IDENTIFY);
  identificador["username"] = nombre;
  return convierteACadena(identificador);
}

std::string MensajeJson::manejaMensajeCliente(char buffer[]){
  std::vector<std::string> buff = convierteAVector(buffer);

  if(buff[0] == "request"){
    //No se puede hacer switch para string.
    if(buff[1] == "-s"){

    }else if(buff[1] == "-u"){
      
    }else if(buff[1] == "-t"){
      
    }else if(buff[1] == "-nr"){
      
    }else if(buff[1] == "-i"){
      
    }else if(buff[1] == "-jr"){
      
    }else if(buff[1] == "-ru"){
      
    }else if(buff[1] == "-lr"){
      
    }else if(buff[1] == "-d"){
      
    }
  }
}

int MensajeJson::manejaRespuestaServidor(char buffer[]){
  Json::Value buff = convierteAJson(buffer);

  if(buff["type"] == TipoServidor::getString(TipoServidor::Tipo::RESPONSE)){
    if(buff["operation"] == TipoCliente::getString(TipoCliente::Tipo::IDENTIFY)){
      return respuestaIdentificaUsuario(buff);
    }
  }
  
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

int MensajeJson::respuestaIdentificaUsuario(Json::Value respuesta){
  
  if(respuesta["result"] == ResultadoServidor::getString(ResultadoServidor::Resultado::SUCCESS)){
      return 1;
    }
    return -1;
}


