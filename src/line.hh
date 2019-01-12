#pragma once

#include <string>

using namespace std;

class Line {
private:
  string m_prefix;
  string m_text;
public:
  Line(string prefix, string text) {
    m_prefix = prefix;
    m_text = text;
  }

  Line() {
    m_prefix = "";
    m_text = "";
  }
  string render() {
    return m_prefix + m_text;
  }
  void prefix(string s) {
    m_prefix = s;
  }
  void append(string s) {
    m_text += s;
  }
  void pop_back() {
    m_text.pop_back();
  }
  
};

