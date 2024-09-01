#ifndef TIPOPETICION_H
#define TIPOPETICION_H

#include <string>

enum class Tipos{
  //Se identifica el ussuario.
  IDENTIFY = -5,
  //Cambia el estatus del ususario.
  STATUS = -6,
  //Pide la lista de usuarios.
  USERS = -7,
  //Manda texto privado a un usuario,
  TEXT = -8,
  //Manda un mensaje publico.
  PUBLIC_TEX = -9,
  //Crea una nueva sala.
  NEW_ROOM = -10,
  //Invita a uno o más usuarios a una sala.
  INVITE= -11,
  //El usuario se une a una sala.
  JOIN_ROOM = -12,
  //Pide la lista de usuarios.
  ROOM_USERS = -13,
  //Manda un mensaje a la sala.
  ROOM_TEXT = -14,
  //Abandona una sala.
  LEAVE_ROOM = -15,
  //El usuario se desconecta.
  DISCONNECT = -16,
  
};

#endif 
