/**
 * @class InvalidOperationException
 * @brief Excepción lanzada cuando se recibe un objeto de tipo Operacion
 *        en una función que no lo admite.
 *
 * Esta excepción se usa para indicar que un objeto Operacion ha sido 
 * ingresado en un contexto donde no se espera ese tipo. Es útil para 
 * detectar errores lógicos en tiempo de ejecución, cuando el tipo de 
 * operación no es válido para la función o flujo actual.
 */

#include <exception>
#include <iostream>
#include <string>

class InvalidOperationException : public std::exception{
  std::string message;

public:
  InvalidOperationException(const char* msg) : message(msg){}

  const char* what() const throw(){
    return message.c_str();
  }
};
