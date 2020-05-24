#pragma once

#include <map>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

#include "token.h"

using namespace ranges;

namespace csv {

typedef std::map<std::string, std::string> row;

row parse(std::vector<token> tokens, std::vector<std::string> field_names) {
  auto is_identifier = [](token token) { return token.is_identifier(); };
  auto yield_value = [](token token) { return token.value; };
  auto columns = tokens | views::filter(is_identifier) |
                 views::transform(yield_value) | to<std::vector<std::string>>();

  // Why doesn't this work?
  // return views::zip(field_names, columns) | to<std::map>();
  row row;
  for (size_t i = 0; i < field_names.size(); ++i)
    row[field_names[i]] = columns[i];
  return row;
}

}  // namespace csv
