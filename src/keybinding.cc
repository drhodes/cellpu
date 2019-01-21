#include <iostream>
#include <string>
#include <map>
#include <optional>

#include "keybinding.hh"

void
KeyBindings::bindKey(string key, string cmd) {
  std::cerr << "Binding: " << key << " -> " << cmd << endl;
  m_keybindings[key] = cmd;
}

std::optional<string>
KeyBindings::getKeyBind(string key) {  
  auto binding = m_keybindings.find(key);
  if (binding == std::end(m_keybindings)) {
    return nullopt;
  } else {
    return make_optional(binding->second);
  }
}
