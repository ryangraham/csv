#include <fstream>
#include <iostream>
#include <string>

#include "csv.h"

using namespace ranges;

int main() {
  std::string file_name = "country.csv";
  std::fstream ifs(file_name);

  if (!ifs) return 1;

  auto reader = csv::map_reader(ifs);

  for (std::string field_name : reader.field_names)
    std::cout << field_name << std::endl;

  auto print_map = [](auto&& map) {
    for (const auto& [k, v] : map) std::cout << k << "=" << v << std::endl;
  };
  for (auto&& row : reader.rows()) print_map(row);

  return 0;
}
