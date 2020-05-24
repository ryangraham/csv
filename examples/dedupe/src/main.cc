#include <csv/csv.h>

#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::string file_name = "../country.csv";
  std::fstream ifs(file_name);

  if (!ifs) return 1;

  auto reader = csv::map_reader(ifs);

  // auto print_map = [](auto&& map) {
  //   for (const auto& [k, v] : map) std::cout << k << "=" << v << std::endl;
  // };
  // for (auto&& row : reader.rows()) print_map(row);

  return 0;
}
