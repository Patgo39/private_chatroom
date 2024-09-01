#idndef MENSAJEJSON_H
#define MENSAJEJSON_H

#include <iostream>
#include <json/json.h>
#include <string>

class PeticionesJson{
  const std::String identify = "IDENTIFY";
public:
  static Json::Value convierteAJson(char buffer[]);
  static const std::string convierteACadena(Json::Value);
  static Json::Value writeIdentificadorUsuario(std::string);
  static Json::Value writeCambiaEstado(std::string);

#endif
