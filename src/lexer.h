#pragma once

#include <iostream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

#include "token.h"

using namespace ranges;

namespace csv {

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
    char c = peek();

    if (c == '"') quote_count++;

    switch (c) {
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
    if (c == '"') quote_count++;

    switch (c) {
      case '\0':
        return false;
      case ',':
        return (inside_quote_context()) ? true : false;
      default:
        return true;
    }
  }

  bool inside_quote_context() { return quote_count % 2 == 1; }
  int quote_count = 0;
  const char* begin = nullptr;
};

}  // namespace csv