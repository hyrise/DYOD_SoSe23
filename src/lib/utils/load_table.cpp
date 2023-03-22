#include "load_table.hpp"

#include <fstream>

#include <boost/lexical_cast.hpp>

#include "resolve_type.hpp"
#include "storage/table.hpp"
#include "utils/assert.hpp"

namespace {

std::vector<std::string> split(const std::string& str, char delimiter) {
  auto result = std::vector<std::string>{};
  auto stream = std::stringstream{str};
  auto token = std::string{};

  while (std::getline(stream, token, delimiter)) {
    result.push_back(token);
  }

  return result;
}

}  // namespace

namespace opossum {

std::shared_ptr<Table> load_table(const std::string& file_name, size_t chunk_size) {
  auto infile = std::ifstream{file_name};
  Assert(infile.is_open(), "load_table: Could not find file " + file_name);

  auto line = std::string{};
  std::getline(infile, line);
  const auto column_names = split(line, '|');
  std::getline(infile, line);
  const auto column_types = split(line, '|');

  const auto table = std::make_shared<Table>(chunk_size);
  const auto column_count = column_names.size();
  Assert(column_types.size() == column_count, "Mismatching number of column types.");
  for (auto column_id = ColumnID{0}; column_id < column_count; ++column_id) {
    table->add_column(column_names[column_id], column_types[column_id], false);
  }

  while (std::getline(infile, line)) {
    const auto string_values = split(line, '|');
    Assert(string_values.size() == column_count, "Mismatching number of values.");
    auto variant_values = std::vector<AllTypeVariant>{};
    variant_values.reserve(column_count);

    for (auto column_id = ColumnID{0}; column_id < column_count; ++column_id) {
      resolve_data_type(column_types[column_id], [&](auto data_type_t) {
        using ColumnDataType = typename decltype(data_type_t)::type;
        variant_values.emplace_back(boost::lexical_cast<ColumnDataType>(string_values[column_id]));
      });
    }

    table->append(variant_values);
  }
  return table;
}

}  // namespace opossum
