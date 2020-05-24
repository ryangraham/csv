#pragma once

#include <iostream>
#include <istream>
#include <map>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

#include "lexer.h"
#include "parser.h"

using namespace ranges;

namespace csv {

struct map_reader {
 private:
  std::istream* sin_;

  void get_field_names() {
    std::string first_line;
    std::getline(*sin_, first_line);
    field_names =
        first_line | views::split(',') | ranges::to<std::vector<std::string>>();
  }

 public:
  std::vector<std::string> field_names;
  map_reader(std::istream& sin) : sin_(&sin) { get_field_names(); }

  std::vector<row> rows() {
    std::vector<row> results;
    auto lex = [](const std::string& s) {
      lexer lexer(s);
      return lexer.tokens();
    };
    auto lines = getlines(*sin_) | views::transform(lex);

    for (auto&& line : lines) {
      auto row = parse(line, field_names);
      results.push_back(row);
    }

    return results;
  }
};

}  // namespace csv