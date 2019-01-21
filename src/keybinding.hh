#pragma once

#include <string>
#include <map>

using namespace std;

class KeyBindings {
private:
  std::map<string, string> m_keybindings;
  
public:
  void bindKey(string key, string cmd);
  std::optional<string> getKeyBind(string key);
};
