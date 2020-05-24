#pragma once

#include <iostream>
#include <istream>
#include <map>
#include <range/v3/all.hpp>
#include <range/v3/view/facade.hpp>
#include <string>
#include <vector>

#include "lexer.h"

using namespace ranges;

namespace csv {

typedef std::map<std::string, std::string> row;

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
    auto lex = [](const std::string& s) {
      lexer lexer(s);
      return lexer.tokens();
    };
    auto lines = getlines(*sin_) | views::transform(lex);

    for (auto&& l : lines)
      for (auto&& x : l) std::cout << x.value << " " << x.type_str << std::endl;

    std::vector<row> results;
    return results;
  }
};

}  // namespace csv