#ifndef SCREEN_h
#define SCREEN_h

#include <iostream>
#include <string>

class Screen{

  std::string youString;
  int bufferSize;
  
  
 public:
  Screen(int bufferSize);

  std::string askAndGetPort();

  std::string askAndGetIp();
  
  void showMessage(std::string name, char buffer[], bool general, bool serverResponse);

  std::string getMessage();
};


#endif
