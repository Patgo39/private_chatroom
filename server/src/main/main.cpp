#include <iostream>
#include "server.h"

int main(){
  int port;
  const int bufferSize = 1024;
  std::cout<<"Type the port: ";
  std::cin>>port;
  Server s = Server(port, bufferSize);
  s.start();
  return 0;
}
