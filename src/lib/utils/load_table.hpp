#pragma once

#include <memory>
#include <string>

namespace opossum {

class Table;

// This is a helper method which is heavily used in our test suite.
std::shared_ptr<Table> load_table(const std::string& file_name, size_t chunk_size);

}  // namespace opossum
