#include "ManejaPeticionCliente.h"

std::string ManejaPeticionCliente::convierteACadena(Json::Value objetoJson){
  Json::StreamWriterBuilder builder;
  const std::string output = Json::writeString(builder, objetoJson);

  return output;
}

Json::Value ManejaPeticionCliente::convierteAJson(char buffer[]){
  Json::Value bufferJson;
  Json::CharReaderBuilder builder;
  JSONCPP_STRING errs;
  std::istringstream s(buffer);

  parseFromStream(builder, s, &bufferJson, &errs);

  return bufferJson;
}

int ManejaPeticionCliente::manejaPeticion(char buffer[]){
  Json::Value peticion = convierteAJson(buffer);
  int tipo = TipoCliente::getTipo(peticion["type"].asString());
  return tipo;
}

std::string ManejaPeticionCliente::manejaIdentificacion(char buffer[], std::map<int,Usuario> mapa, bool &valido, std::string &nombre){
  Json::Value identificacion = convierteAJson(buffer);
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
    return convierteACadena(respuesta);
}

Json::Value ManejaPeticionCliente::regresaRespuesta(TipoCliente::Tipo operacion, ResultadoServidor::Resultado resultado, std::string extra){
  Json::Value respuesta;
  respuesta["type"] = TipoServidor::getString(TipoServidor::Tipo::RESPONSE);
  respuesta["operation"] = TipoCliente::getString(operacion);
  respuesta["result"] = ResultadoServidor::getString(resultado);
  respuesta["extra"] = extra;
  
  return respuesta;
}
