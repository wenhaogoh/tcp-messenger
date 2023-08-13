#pragma once
#include "../message/message.h"
#include <vector>
#include <shared_mutex>

class Inbox
{
public:
  void add(const Message &message);
  std::vector<Message> read();

private:
  std::shared_mutex shared_mutex_;
  std::vector<Message> messages;
};