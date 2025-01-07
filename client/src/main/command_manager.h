#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <iostream>
#include <string>
#include <json/json.h>
#include <vector>
#include <sstream>
#include "command_exception.cpp"

class CommandManager{
  
 public:
  CommandManager();
  std::string getJsonFromCommand(std::string userMessage);

 private:
  std::vector<std::string> getCommandAsVector(std::string userMessage);
};

#endif
