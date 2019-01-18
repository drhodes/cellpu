#include <iostream>
#include <string>
#include <map>

#include "keybinding.hh"

KeyBindings::KeyBindings() {
}

void
KeyBindings::bindKey(string key, string cmd) {
  std::cerr << "Binding: " << key << " -> " << cmd << endl;
  m_keybindings[key] = cmd;
}

string
KeyBindings::getKeyBind(string key) {  
  auto binding = m_keybindings.find(key);
  if (binding == std::end(m_keybindings)) {
    return "unknown-binding";
  } else {
    return binding->second;
  }
}
