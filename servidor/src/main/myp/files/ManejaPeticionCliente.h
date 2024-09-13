#ifndef MANEJAPETICIONCLIENTE_H
#define MANEJAPETICIONCLIENTE_H

#include <iostream>
#include <json/json.h>
#include <string>
#include "TipoCliente.h"
#include "TipoServidor.h"
#include "ResultadoServidor.h"
#include <map>
#include <vector>
#include "Usuario.h"
#include "Cuarto.h"

class ManejaPeticionCliente{
public:
  static int manejaPeticion(std::string);
  static std::string manejaIdentificacion(std::string, std::map<int, Usuario> &mapa, bool&, std::string&, std::string&);
  static std::string manejaTextoPublico(std::string, std::string);
  static std::string manejaDesconexion(std::string);
  static std::string manejaCambioEstado(std::string, int, std::map<int, Usuario>&, bool&);
  static std::string manejaListaGeneral(std::map<int, Usuario>&);
  static std::string manejaMensajePrivado(std::string, std::map<int, Usuario>&, int, int&);
  static std::string manejaNuevoCuarto(std::string, Cuarto&, std::vector<Cuarto>&, int);
  static std::string manejaInvitacion(std::string, std::vector<Cuarto>&, bool&, std::map<int, Usuario>, std::vector<int>&, int);
  
  static std::string manejaUnionACuarto(std::string, std::string&, std::vector<Cuarto>&, bool&, Usuario, Cuarto&);

  static std::string manejaListaCuarto(std::string, std::vector<Cuarto>&, std::map<int, Usuario>&, int);

  static std::string manejaMensajeCuarto(std::string, Cuarto&, std::vector<Cuarto>&, bool&, Usuario us);

  static std::string manejaDejarCuarto(std::string, Cuarto&, std::vector<Cuarto>&, bool&, Usuario us);
private:
  static Json::Value convierteAJson(std::string);
  static std::string convierteACadena(Json::Value);
  static Json::Value regresaRespuesta(TipoCliente::Tipo, ResultadoServidor::Resultado, std::string);
  static bool existeCuarto(std::string, std::vector<Cuarto>&, Cuarto&);
};
#endif
