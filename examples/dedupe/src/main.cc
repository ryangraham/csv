#include <csv/csv.h>

#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::string input_file_name = "../input.csv";
  std::fstream ifs(input_file_name);

  if (!ifs) return 1;

  auto reader = csv::map_reader(ifs);

  std::string output_file_name = "../output.csv";
  std::ofstream ofs(output_file_name);
  if (!ofs) return 1;

  std::vector<std::string> field_names = reader.field_names;
  auto writer = csv::map_writer(ofs, field_names);
  writer.write_header();

  auto rows = reader.rows() | actions::sort | actions::unique;

  for (auto&& row : rows) writer.write_row(row);

  ofs.close();
  return 0;
}
