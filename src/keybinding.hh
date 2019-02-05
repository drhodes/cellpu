#pragma once

#include <experimental/optional>
#include <map>
#include <string>
using namespace std;
using namespace std::experimental;

class KeyBindings {
 private:
  std::map<string, string> m_keybindings;

 public:
  void bindKey(string key, string cmd);
  optional<string> getKeyBind(string key);
};
