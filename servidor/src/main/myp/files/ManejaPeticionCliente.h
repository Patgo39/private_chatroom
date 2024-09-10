#ifndef MANEJAPETICIONCLIENTE_H
#define MANEJAPETICIONCLIENTE_H

#include <iostream>
#include <json/json.h>
#include <string>
#include "TipoCliente.h"
#include "TipoServidor.h"
#include "ResultadoServidor.h"
#include <map>
#include "Usuario.h"

class ManejaPeticionCliente{
public:
  static int manejaPeticion(std::string);
  static std::string manejaIdentificacion(std::string, std::map<int, Usuario> &mapa, bool&, std::string&, std::string&);
  static std::string manejaTextoPublico(std::string, std::string);
  static std::string manejaDesconexion(std::string);
  static std::string manejaCambioEstado(std::string, int, std::map<int, Usuario>&, bool&);
private:
  static Json::Value convierteAJson(std::string);
  static std::string convierteACadena(Json::Value);
  static Json::Value regresaRespuesta(TipoCliente::Tipo, ResultadoServidor::Resultado, std::string);
};
#endif
