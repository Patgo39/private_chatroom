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
    mapa[clientSocket].setEstado(estado);
    return convierteACadena(respuesta);
  }else if(estado == EstadoCliente::getString(EstadoCliente::Estado::BUSY)){
    mapa[clientSocket].setEstado(estado);
    return convierteACadena(respuesta);
  }else if(estado == EstadoCliente::getString(EstadoCliente::Estado::ACTIVE)){
    mapa[clientSocket].setEstado(estado);
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

std::string ManejaPeticionCliente::manejaListaGeneral(std::map<int, Usuario>& mapa){
  Json::Value respuesta;
  Json::Value listaUsuarios;
  respuesta["type"] = TipoServidor::getString(TipoServidor::Tipo::USER_LIST);
  std::string nombre;
  std::string status;
  for(auto& elemento: mapa){
    nombre = elemento.second.getNombre();
    status = elemento.second.getEstado();
    listaUsuarios[nombre] = status;
  }

  respuesta["users"] = listaUsuarios;
  return convierteACadena(respuesta);
}

std::string ManejaPeticionCliente::manejaMensajePrivado(std::string peticion, std::map<int, Usuario> &mapa, int clientSocket, int &socketDestinatario){
  Json::Value respuesta;
  Json::Value pet = convierteAJson(peticion);
  std::string nombre = pet["username"].asString();
  std::string texto = pet["text"].asString();

  for(auto& elemento: mapa){
    if(nombre == elemento.second.getNombre()){
      respuesta["type"] = TipoServidor::getString(TipoServidor::Tipo::TEXT_FROM);
      respuesta["username"] = mapa[clientSocket].getNombre();
      respuesta["text"] = texto;
      socketDestinatario = elemento.first;
      return convierteACadena(respuesta);
    }
  }

  respuesta = regresaRespuesta(TipoCliente::Tipo::TEXT, ResultadoServidor::Resultado::NO_SUCH_USER, nombre);
  return convierteACadena(respuesta);
}

std::string ManejaPeticionCliente::manejaNuevoCuarto(std::string peticion, Cuarto &cuarto, std::vector<Cuarto> &cuartos){
  
  Json::Value pet = convierteAJson(peticion);
  Json::Value respuesta;
  std::string nombre = pet["roomname"].asString();
  for(Cuarto c: cuartos){
    if(c.getNombre() == nombre){
      respuesta = regresaRespuesta(TipoCliente::Tipo::NEW_ROOM, ResultadoServidor::Resultado::ROOM_ALREADY_EXISTS, nombre);
      return convierteACadena(respuesta);
    }
  }
  cuarto = Cuarto(nombre);
  cuartos.push_back(cuarto);

  respuesta = regresaRespuesta(TipoCliente::Tipo::NEW_ROOM, ResultadoServidor::Resultado::SUCCESS, nombre);

  return convierteACadena(respuesta);
}
/**
 * Maneja el json del cliente al invitar a varios usuarios. Regresa el string
 * del Json con la respuesta a la petición.
 * @param peticion la cadena del Json de la petición.
 * @param cuartos el vector de cuartos del servidor.
 * @param valido si la petición el válida es true y false en otro caso.
 * @param mapaUsuarios el mapa del servidor que asocia los sockets con
 * instancias deUsuario.
 * @param clientesAInvitar el vector de sockets de clietes a invitar.
 */
std::string ManejaPeticionCliente::manejaInvitacion(std::string peticion, std::vector<Cuarto> &cuartos, bool &valido, std::map<int, Usuario> mapaUsuarios, std::vector<int> &clientesAInvitar, int clientSocket){
  
  //Json de la petición.
  Json::Value pet = convierteAJson(peticion);
  
  //El Json de la respuesta a la petición.
  Json::Value respuesta;
  
  //El arreglo Json de la lista de invitados.
  Json::Value arregloInvitados = pet["usernames"];
  
  //El cuarto que recibirá a los invitados de la lista.
  Cuarto cuarto;
  
  //Nombre del cuarto que recibirá a los invitados.
  std::string nombreCuarto = pet["roomname"].asString();
  
  //Booleano que especifica si existe el cuarto de la petición.
  bool existeCuarto = false;
  
  //Mapa de usuarios de la lista general que asocia los nombres con los sockets.
  std::map<std::string, int> usuariosSockets;

  //Se revisa si existe el cuarto.
  for(Cuarto c:cuartos){
    if(nombreCuarto == c.getNombre()){
      existeCuarto = true;
      cuarto = c;
    }
  }
  //Si no existe el cuarto se regresa un Json de respuesta tipo NO_SUCH_ROOM.
  if(!existeCuarto){
    respuesta = regresaRespuesta(TipoCliente::Tipo::INVITE, ResultadoServidor::Resultado::NO_SUCH_ROOM, nombreCuarto);
    valido = false;
    return convierteACadena(respuesta);
  }

  //Crea el mapa de usuarios en el servidor que relaciona nombres con sockets.
  for(auto elemento:mapaUsuarios){
    usuariosSockets[elemento.second.getNombre()] = elemento.first;
  }

  //Se obtiene un vector de cadenas de la lista de invitados.
  std::vector<std::string> vectorInvitados(arregloInvitados.begin(), arregloInvitados.end());
  //std::vector<std::string> vectorInvitados;
  //Se revisa si existen los usuarios del vector de invitados.
  for(std::string username: vectorInvitados){
    if(usuariosSockets.find(username) != usuariosSockets.end()){
      respuesta = regresaRespuesta(TipoCliente::INVITE, ResultadoServidor::Resultado::NO_SUCH_USER, username);
      return convierteACadena(respuesta);
    }else{
      //Se crea el vector de sockets de clientes innvitados.
      int socket = usuariosSockets[username];
      clientesAInvitar.push_back(socket);
      //Se le indica al cuarto que un usuario fue invitado.
      cuarto.registraUsuario(socket);
    }
  }

  //Crea el Json que se enviará a los usuarios invitados.
  respuesta["type"] = TipoServidor::getString(TipoServidor::Tipo::INVITATION);
  respuesta["username"] = mapaUsuarios[clientSocket].getNombre();
  respuesta["roomname"] = nombreCuarto;

  return convierteACadena(respuesta);
}

std::string ManejaPeticionCliente::manejaUnionACuarto(std::string peticion, std::string &mensajeGeneral, std::vector<Cuarto> &cuartos, bool &valido, std::string nombre){

  return "Hola";
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
