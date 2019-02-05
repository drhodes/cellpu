#include <experimental/optional>
#include <iostream>
#include <map>
#include <string>

#include "keybinding.hh"
using namespace std::experimental;

void
KeyBindings::bindKey(string key, string cmd) {
  std::cerr << "Binding: " << key << " -> " << cmd << endl;
  m_keybindings[key] = cmd;
}

optional<string>
KeyBindings::getKeyBind(string key) {
  auto binding = m_keybindings.find(key);
  if (binding == std::end(m_keybindings)) {
    return nullopt;
  } else {
    return make_optional(binding->second);
  }
}
