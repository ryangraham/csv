#pragma once

#include <string>
#include <vector>

#define ENUM_LIST(X) \
  X(COMMA)           \
  X(IDENTIFIER)      \
  X(END)

#define AS_ENUM(e) e,

#define AS_STRING(E) #E,

namespace csv {

constexpr char const* token_type_names[] = {ENUM_LIST(AS_STRING)};
enum struct token_type { ENUM_LIST(AS_ENUM) };
char const* token_type_name(token_type const val) {
  return token_type_names[static_cast<int>(val)];
}

struct token {
 public:
  token(token_type type, const char* begin, const char* end)
      : type{type}, value(begin, std::distance(begin, end)) {
    type_str = token_type_name(type);
  }
  token(token_type type, const char* begin, int len)
      : type{type}, value(begin, len) {
    type_str = token_type_name(type);
  }

  bool is_identifier() { return type == token_type::IDENTIFIER; }

  token_type type{};
  std::string_view type_str{};
  std::string_view value{};
};

}  // namespace csv
