#include <iostream>
#include "./view/screen.h"

int main(){
  const int maxSizeBuffer = 1024;
  Screen sc = Screen(maxSizeBuffer);

  std::string port = sc.askAndGetPort();
  std::string ip = sc.askAndGetIp();
  std::string userMessage = sc.getMessage();
  
  return 0;
}
