#include "MensajeJson.h"

static Json::Value PeticionesJson::convierteAJson(char buffer[]){
  Json::Value bufferJson;
  Json::CharReaderBuilder builder;
  JSONCPP_STRING errs;
  std::istringstream s(buffer);

  parseFromStream(builder, s, &bufferJson, &errs);

  return bufferJson;
}

static const std::string PeticionesJson::convierteACadena(Json::Value objetoJson){
  Json::StreamWriterBuilder builder;
  const std::string output = Json::writeString(builder, objetoJson);

  return output;
}

static Json::Value PeticionesJson:writeIdentificadorUsuario(std::string nombre){
  Json::Value identificador;
  identificador["type"] = "IDENTIFY";
  identificador["username"] = nombre;

  return identificador;
}

static Json::Value writeCambiaEstado(std::string estado){
  Json::Value identificador;
  identificador["type"] = "STATUS";
  identificador["status"] = estado;

  return identificador;
}


