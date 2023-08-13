#pragma once
#include "client_manager.h"

class Command
{
public:
  virtual void execute(ClientManager &client_manager) = 0;
};