#pragma once

#include <iostream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

#define ENUM_LIST(X) \
  X(COMMA)           \
  X(IDENTIFIER)      \
  X(END)

#define AS_ENUM(e) e,

#define AS_STRING(E) #E,

using namespace ranges;

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

  token_type type{};
  std::string_view type_str{};
  std::string_view value{};
};

struct lexer {
 public:
  lexer(const std::string& line) : begin(line.c_str()) {}

  std::vector<token> tokens() {
    std::vector<token> results;

    token token = next();
    results.push_back(token);

    while (token.type != token_type::END) {
      token = next();
      results.push_back(token);
    }

    return results;
  }

 private:
  char peek() const { return *begin; }
  char get() { return *begin++; }

  token next() {
    switch (peek()) {
      case '\0':
        return atom(token_type::END);
      case ',':
        return atom(token_type::COMMA);
      default:
        return identifier();
    }
  }

  token atom(token_type type) { return token(type, begin++, 1); }
  token identifier() {
    const char* start = begin;
    get();
    while (is_identifier(peek())) get();
    return token(token_type::IDENTIFIER, start, begin);
  }

  bool is_identifier(char c) {
    switch (c) {
      case '\0':
        return false;
      case ',':
        return (inside_quote_context()) ? true : false;
      case '"':
        quote_count++;
        return true;
      default:
        return true;
    }
  }

  bool inside_quote_context() { return quote_count % 2 == 0; }
  int quote_count = 0;
  const char* begin = nullptr;
};

}  // namespace csv