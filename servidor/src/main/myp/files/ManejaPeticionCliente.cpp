#include "ManejaPeticionCliente.h"

int ManejaPeticionCliente::manejaPeticion(std::string buffer){
  Json::Value peticion = convierteAJson(buffer);
  int tipo = TipoCliente::getTipo(peticion["type"].asString());
  return tipo;
}

std::string ManejaPeticionCliente::manejaIdentificacion(std::string buffer, std::map<int,Usuario> &mapa, bool &valido, std::string &nombre, std::string &notificacion){
  
  Json::Value identificacion = convierteAJson(buffer);
  Json::Value notif;
  nombre = identificacion["username"].asString();
  Json::Value respuesta;
  
  for(auto& elemento: mapa){
    if(nombre == elemento.second.getNombre()){
      respuesta = regresaRespuesta(TipoCliente::Tipo::IDENTIFY, ResultadoServidor::Resultado::USER_ALREADY_EXISTS, nombre);
      valido = false;
      return convierteACadena(respuesta);
    }
  }
  
  respuesta = regresaRespuesta(TipoCliente::Tipo::IDENTIFY, ResultadoServidor::Resultado::SUCCESS, nombre);

  notif["type"] = TipoServidor::getString(TipoServidor::Tipo::NEW_USER);
  notif["username"] = nombre;
  notificacion = convierteACadena(notif);
  return convierteACadena(respuesta);
}

std::string ManejaPeticionCliente::manejaTextoPublico(std::string solicitud, std::string nombre){
  Json::Value solic = convierteAJson(solicitud);
  Json::Value respuesta;
  respuesta["type"] = TipoServidor::getString(TipoServidor::Tipo::PUBLIC_TEXT_FROM);
  respuesta["username"] = nombre;
  respuesta["text"] = solic["text"].asString();
  
  return convierteACadena(respuesta);
}

std::string ManejaPeticionCliente::manejaDesconexion(std::string nombre){
  Json::Value aviso;
  aviso["type"] = TipoServidor::getString(TipoServidor::Tipo::DISCONNECTED);
  aviso["username"] = nombre;

  return convierteACadena(aviso);
}

std::string ManejaPeticionCliente::manejaCambioEstado(std::string peticion, int clientSocket, std::map<int, Usuario> &mapa, bool &valido){
  Json::Value pet = convierteAJson(peticion);
  Json::Value respuesta;
  std::string estado = pet["status"].asString();
  
  respuesta["type"] = TipoServidor::getString(TipoServidor::Tipo::NEW_STATUS);
  respuesta["status"] = estado;
  respuesta["username"] = mapa[clientSocket].getNombre();
  if(estado == EstadoCliente::getString(EstadoCliente::Estado::AWAY)){
    mapa[clientSocket].setEstado(peticion);
    return convierteACadena(respuesta);
  }else if(estado == EstadoCliente::getString(EstadoCliente::Estado::BUSY)){
    mapa[clientSocket].setEstado(peticion);
    return convierteACadena(respuesta);
  }else if(estado == EstadoCliente::getString(EstadoCliente::Estado::ACTIVE)){
    mapa[clientSocket].setEstado(peticion);
      return convierteACadena(respuesta);
  }
  valido = false;
  respuesta.removeMember("status");
  respuesta.removeMember("username");
  respuesta["type"] = TipoServidor::getString(TipoServidor::Tipo::RESPONSE);
  respuesta["operation"] = TipoServidor::getString(TipoServidor::Tipo::INVALID);
  respuesta["result"] = TipoServidor::getString(TipoServidor::Tipo::INVALID);
  return convierteACadena(respuesta);
}

std::string ManejaPeticionCliente::convierteACadena(Json::Value objetoJson){
  Json::StreamWriterBuilder builder;
  const std::string output = Json::writeString(builder, objetoJson);
  
  return output;
}

Json::Value ManejaPeticionCliente::convierteAJson(std::string buffer){
  Json::Value bufferJson;
  Json::Reader reader;
  reader.parse(buffer, bufferJson);

  return bufferJson;
}

Json::Value ManejaPeticionCliente::regresaRespuesta(TipoCliente::Tipo operacion, ResultadoServidor::Resultado resultado, std::string extra){
  Json::Value respuesta;
  respuesta["type"] = TipoServidor::getString(TipoServidor::Tipo::RESPONSE);
  respuesta["operation"] = TipoCliente::getString(operacion);
  respuesta["result"] = ResultadoServidor::getString(resultado);
  respuesta["extra"] = extra;
  
  return respuesta;
}
