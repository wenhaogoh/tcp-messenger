#include "inbox.h"

void Inbox::add(const Message &message)
{
  std::unique_lock lock(shared_mutex_);
  messages.push_back(message);
}

std::vector<Message> Inbox::read()
{
  std::unique_lock lock(shared_mutex_);
  std::vector<Message> res = std::vector<Message>(messages);
  messages.clear();
  return res;
}