#pragma once

#include <iostream>
#include <map>
#include <ostream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

using namespace ranges;

namespace csv {

struct map_writer {
 private:
  std::ostream* sout_;
  std::vector<std::string> field_names_;

 public:
  map_writer(std::ostream& sout, std::vector<std::string> field_names)
      : sout_(&sout), field_names_{field_names} {}

  void write_header() {
    auto header = field_names_ | views::join(',') | to<std::string>();
    *sout_ << header << std::endl;
    std::flush(*sout_);
  }

  void write_row(std::map<std::string, std::string> row) {
    auto row_str = row | views::values | view::join(',') | to<std::string>();
    *sout_ << row_str << std::endl;
  }
};

}  // namespace csv
