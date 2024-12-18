#include <iostream>
#include "./view/screen.h"

int main(){
  const int maxSizeBuffer = 1024;
  Screen sc = Screen(maxSizeBuffer);

  std::string port = sc.askAndGetPort();
  std::string ip = sc.askAndGetIp();

  while(true){
    std::string userMessage = sc.getMessage();

    std::cout<<"x: "<<userMessage<<std::endl;
  }
  
  return 0;
}
