#pragma once

#include <string>
#include <map>

using namespace std;

class KeyBindings {
private:
  std::map<string, string> m_keybindings; 
public:
  KeyBindings();
  void bindKey(string key, string cmd);
  string getKeyBind(string key);

};