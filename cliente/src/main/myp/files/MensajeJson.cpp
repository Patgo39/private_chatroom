#include "MensajeJson.h"

std::string MensajeJson::finColor = "\033[0m";
std::map<std::string, int> MensajeJson::coloresUsuarios;
int MensajeJson::contador = 3;

std::string MensajeJson::peticionIdentificaUsuario(std::string nombre){
  
  Json::Value identificador;
  identificador["type"] = TipoCliente::getString(TipoCliente::Tipo::IDENTIFY);
  identificador["username"] = nombre;
  return convierteACadena(identificador);
}

std::string MensajeJson::manejaMensajeCliente(char buffer[], bool &sigueConectado, std::string &estado){
  std::vector<std::string> buff = convierteAVector(buffer);

  if(buff[0] == "REQUEST"){
    //No se puede hacer switch para string.
    //Peticion cambio de estado.
    if(buff[1] == "-s"){
      if(buff.size() != 3){
	std::cout<<"Formato del comando incorrecto."<<std::endl;
	std::cout<<"Uso: REQUEST -s 'NuevoEstado'"<<std::endl;
	return "NULL";
      }
      return peticionCambiaEstado(buff, estado);
      
    }
    //Peticion lista de usuarios.
    else if(buff[1] == "-u"){
      if(buff.size() != 2){
	std::cout<<"Formato del comando incorrecto."<<std::endl;
	std::cout<<"Uso: REQUEST -u"<<std::endl;
	return "NULL";
      }
      return peticionListaGeneral();
      
    }
    //Peticion Mensaje Privado.
    else if(buff[1] == "-t"){
      if(buff.size() < 4){
	std::cout<<"Formato del comando incorrecto."<<std::endl;
	std::cout<<"Uso: REQUEST -d"<<std::endl;
	return "NULL";
      }
      return peticionMensajePrivado(buff);
      
    }else if(buff[1] == "-nr"){
      
    }else if(buff[1] == "-i"){
      
    }else if(buff[1] == "-jr"){
      
    }else if(buff[1] == "-ru"){
      
    }else if(buff[1] == "-lr"){
      
    }
    //Peticion descinectar.
    else if(buff[1] == "-d"){
      if(buff.size() != 2){
	std::cout<<"Formato del comando incorrecto."<<std::endl;
	std::cout<<"Uso: REQUEST -d"<<std::endl;
	return "NULL";
      }
      sigueConectado = false;
      return peticionDesconectar();
    }else{
      
      std::cout<<"Formato del comando incorrecto."<<std::endl;
      return "NULL";
    }
  }

  return peticionMandaTextoPublico(buffer);
}

int MensajeJson::manejaRespuestaServidor(char buffer[]){
  
  Json::Value buff = convierteAJson(buffer);
  
  if(buff["type"] == TipoServidor::getString(TipoServidor::Tipo::RESPONSE)){
    if(buff["operation"] == TipoCliente::getString(TipoCliente::Tipo::IDENTIFY)){
      return respuestaIdentificaUsuario(buff);
    }else if(buff["operation"] == TipoServidor::getString(TipoServidor::Tipo::INVALID)){
      return respuestaPeticionInvalida(buff);
    }else if(buff["operation"] == TipoCliente::getString(TipoCliente::Tipo::TEXT)){
      return respuestaMensajePrivado(buff);
    }
    
  }
  return 0;
}

void MensajeJson::manejaAvisoServidor(char buffer[]){
  Json::Value buff = convierteAJson(buffer);
  
  if(buff["type"] == TipoServidor::getString(TipoServidor::Tipo::NEW_USER)){
    avisoNuevoUsuario(buff);
  }else if(buff["type"] == TipoServidor::getString(TipoServidor::Tipo::NEW_STATUS)){
    avisoNuevoEstado(buff);
  }else if(buff["type"] == TipoServidor::getString(TipoServidor::Tipo::USER_LIST)){
    avisoListaGeneral(buff);
  }else if(buff["type"] == TipoServidor::getString(TipoServidor::Tipo::TEXT_FROM)){
    avisoMensajePrivado(buff);
  }else if(buff["type"] == TipoServidor::getString(TipoServidor::Tipo::PUBLIC_TEXT_FROM)){
    avisoTextoPublico(buff);
  }else if(buff["type"] == TipoServidor::getString(TipoServidor::Tipo::JOINED_ROOM)){
      
  }else if(buff["type"] == TipoServidor::getString(TipoServidor::Tipo::ROOM_USER_LIST)){
      
  }else if(buff["type"] == TipoServidor::getString(TipoServidor::Tipo::ROOM_TEXT_FROM)){
      
  }else if(buff["type"] == TipoServidor::getString(TipoServidor::Tipo::LEFT_ROOM)){
      
  }else if(buff["type"] == TipoServidor::getString(TipoServidor::Tipo::DISCONNECTED)){
    avisoUsuarioDesconectado(buff);
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
    std::cout<<"Te has unido a la conversación."<<std::endl;
    return 1;
  }
  std::cout<<"Nombre no disponible, introduzca otro."<<std::endl;
  return -1;
}

int MensajeJson::respuestaPeticionInvalida(Json::Value respuesta){
  if(respuesta["result"].asString() == "NOT_IDENTIFIED"){
    std::cout<<"Usted aún no se ha identificado."<<std::endl;
  }else{
    std::cout<<"Petición inválida, será desconectado."<<std::endl;
  }
  
  return -1;
}

int MensajeJson::respuestaMensajePrivado(Json::Value respuesta){
  if(respuesta["result"] == ResultadoServidor::getString(ResultadoServidor::Resultado::NO_SUCH_USER)){
    std::string nombre = respuesta["extra"].asString();
    std::cout<<"Usuario '"<<nombre<<"' no encontrado."<<std::endl;
  }
  return 1;
}

void MensajeJson::avisoNuevoUsuario(Json::Value aviso){
  std::string nombre = aviso["username"].asString();
  coloresUsuarios[nombre] = getIndice();
  std::cout<<getColor(coloresUsuarios[nombre])<<nombre<<" se unió a la conversación."<<finColor<<std::endl;
}

std::string MensajeJson::peticionMandaTextoPublico(char buffer[]){
  Json::Value mensaje;
  mensaje["type"] = TipoCliente::getString(TipoCliente::Tipo::PUBLIC_TEXT);
  mensaje["text"] = buffer;

  return convierteACadena(mensaje);
}

std::string MensajeJson::peticionDesconectar(){
  Json::Value peticion;
  peticion["type"] = TipoCliente::getString(TipoCliente::Tipo::DISCONNECT);

  return convierteACadena(peticion);
}

std::string MensajeJson::peticionCambiaEstado(std::vector<std::string> vect, std::string &estado){
  estado = vect[2];
  for (auto & c: estado) c = toupper(c);
  Json::Value peticion;
  peticion["type"] = TipoCliente::getString(TipoCliente::Tipo::STATUS);
  peticion["status"] = estado;

  return convierteACadena(peticion);
}

std::string MensajeJson::peticionListaGeneral(){
  Json::Value peticion;
  peticion["type"] = TipoCliente::getString(TipoCliente::Tipo::USERS);

  return convierteACadena(peticion);
}

std::string MensajeJson::peticionMensajePrivado(std::vector<std::string> &vect){
  std::string mensaje = "";
  int i = 0;
  for(std::string s:vect){
    if(i>=3)
    mensaje += s + " ";
    
    i++;
  }

  Json::Value peticion;
  peticion["type"] = TipoCliente::getString(TipoCliente::Tipo::TEXT);
  peticion["username"] = vect[2];
  peticion["text"] = mensaje;
  return convierteACadena(peticion);
}

void MensajeJson::avisoTextoPublico(Json::Value mensaje){
  std::string nombre = mensaje["username"].asString();
  if(!existeUsuario(nombre)){
    coloresUsuarios[nombre] = getIndice();
  }
  std::cout<<getColor(2)<<"CHAT GENERAL "<<finColor<<getColor(coloresUsuarios[nombre])<<nombre<<": "<<finColor<<mensaje["text"].asString()<<std::endl;
}

void MensajeJson::avisoUsuarioDesconectado(Json::Value aviso){
  std::string nombre = aviso["username"].asString();
  std::cout<<getColor(coloresUsuarios[nombre])<<nombre<<" se desconectó."<<finColor<<std::endl;
}

void MensajeJson::avisoNuevoEstado(Json::Value aviso){
  std::string nombre = aviso["username"].asString();
  if(!existeUsuario(nombre)){
    coloresUsuarios[nombre] = getIndice();
  }
  std::string estado = aviso["status"].asString();
  std::cout<<getColor(coloresUsuarios[nombre])<<nombre<<" cambió su estado a "<<estado<<finColor<<std::endl;
}

void MensajeJson::avisoListaGeneral(Json::Value aviso){
  std::cout<<"La Lista de usuarios es: \n"<<aviso["users"]<<std::endl;
}

void MensajeJson::avisoMensajePrivado(Json::Value aviso){
  std::string nombre = aviso["username"].asString();
  std::string mensaje = aviso["text"].asString();
  if(!existeUsuario(nombre)){
    coloresUsuarios[nombre] = getIndice();
  }
  std::cout<<getColor(1)<<"MENSAJE PRIVADO "<<finColor<<getColor(coloresUsuarios[nombre])<<nombre<<": "<<finColor<<mensaje<<std::endl;
}

std::string MensajeJson::getColor(int n){
  return "\033[38;5;" + std::to_string(n) + "m";
}

int MensajeJson::getIndice(){
  int x = contador;
  contador++;
  if(contador >= 256)
    contador = 3;
  return x;
}

bool MensajeJson::existeUsuario(std::string nombre){
  auto it = coloresUsuarios.find(nombre);
    if (it != coloresUsuarios.end()) {
      return true;
    } else {
      return false;
    }
}
