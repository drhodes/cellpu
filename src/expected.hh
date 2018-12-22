

#include <variant>

#define hrm(T) std::variant<T, err>

hrm(int) foo() {
  return 
}
