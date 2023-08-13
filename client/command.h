#pragma once
#include "inbox.h"

class Command
{
public:
  virtual void execute(Inbox &inbox, int socket_fd) = 0;
};