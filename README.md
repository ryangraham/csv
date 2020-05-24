[![Build Status](https://circleci.com/gh/ryangraham/csv.svg?style=svg)](https://circleci.com/gh/ryangraham/csv)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/ryangraham/csv/master/LICENSE)

# CSV

A C++ header-only CSV parser with an interface inspired by Python's DictReader/DictWriter.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)

## Installation

Install csv using [Homebrew](https://brew.sh/).

```
brew tap ryangraham/csv
brew install csv
```

## Usage

```
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
```

Will output something like...

```
FirstName,LastName
Barney,Rubble
Betty,Rubble
Fred,Flintstone
Pebbles,Flintstone
```

## Examples

See [examples](https://github.com/ryangraham/csv/tree/master/examples/).
