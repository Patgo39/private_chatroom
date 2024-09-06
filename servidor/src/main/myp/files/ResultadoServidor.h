/* RespuestaServidor es una enumeración con los resultados de las peticiones
 * del ususario. En su mayoría van en compañía de la enumeración TipoServidor.
 */
#ifndef RESULTADOSERVIDOR_H
#define RESULTADOSERVIDOR_H

#include <iostream>
#include <string>

class ResultadoServidor{
  
 public:
  enum Resultado{
    //Indica que una petición del usuario es exitosa.
    SUCCESS = 24,
    
    //Indica que el nombre de usuario ya está siendo usado.
    USER_ALREADY_EXISTS = 25,
    
    //Indica que el destinatario del mensaje o el usuario invitado no fue encontrado.
    NO_SUCH_USER = 26,
    
    //Indica que el cuarto ya existe.
    ROOM_ALREADY_EXISTS = 27,
    
    //Indica que la sala no existe al hacer una invitación o al momento de unirse o al momento de pedir la lista de usuarios o al momendo de enviar mensaje.
    //También cuando intenta dejar una sala que no existe.
    NO_SUCH_ROOM = 28,
    
    //Indica que el usuario no fue invitado.
    NOT_INVITED = 29,
    
    //Indica que el ususario no se ha unido a la sala o no ha sido invitadocuando pide la lista de usuarios o intenta dejar una sala en la que no está.
    NOT_JOINED = 30
  };

  static std::string getString(ResultadoServidor::Resultado);
};

#endif
