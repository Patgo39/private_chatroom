/* La enumeración TipoServidor contempla todas las respuestas a las peticiones
 * de los usuarios.
 */
#ifndef TIPOSERVIDOR_H
#define TIPOSERVIDOR_H


/* El valor asociado a cada tipo es un múltipo de 5.
 * Por cada petición de parte del usuario cuya enumeración es múltipo de 10, su
 * respuesta será dicho valor, más 5.
 */
enum class TipoServidor{
  //El cliente recibe una respuesta del servidor.
  RESPONSE = -5,
    //Un nuevo usuario se conectó.
    NEW_USER = -15,
    //Notifica a los clientes que un usuario cambió su estado.
    NEW_STATUS = -25,
    //Indica que se mandará la lista de ususarios.
    USER_LIST = -35,
    //Notifica al cliente que recibe un mensaje privado.
    TEXT_FROM = -45,
    //Notifica al cliente que un usuario mandó un texto público.
    PUBLIC_TEXT_FROM = -55,
    //Indica a los usuarios de la sala que un nuevo usuario se unió.
    JOINED_ROOM = -85,
    //Envía al usuario la lista de ususarios de la sala.
    ROOM_USER_LIST = -95,
    //El usuario recibe un dexto en un cuarto.
    ROOM_TEXT_FROM = -105,
    //Indica a los ususarios de la sala que otro usuario se fue.
    LEFT_ROOM = -115,
    //Indica a los usuarios que alguien se desconectó.
    DISCONNECTED = -125
};

#endif
