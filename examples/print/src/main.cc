#include <csv/csv.h>

#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::string input_file_name = "../input.csv";
  std::fstream ifs(input_file_name);

  if (!ifs) return 1;

  auto reader = csv::map_reader(ifs);

  auto headers = reader.field_names | views::join(',') | to<std::string>();
  std::cout << headers << std::endl;

  auto rows = reader.rows() | actions::sort | actions::unique;
  for (auto& row : rows) {
    auto row_str = row | views::values | views::join(',') | to<std::string>();
    std::cout << row_str << std::endl;
  }

  return 0;
}
