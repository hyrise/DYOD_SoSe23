#include "table.hpp"

#include <algorithm>
#include <iomanip>
#include <limits>
#include <memory>
#include <numeric>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "value_segment.hpp"

#include "resolve_type.hpp"
#include "types.hpp"
#include "utils/assert.hpp"

namespace opossum {

Table::Table(const ChunkOffset target_chunk_size) {
  // Implementation goes here
  Fail("Implementation is missing.");
}

void Table::add_column(const std::string& name, const std::string& type) {
  // Implementation goes here
  Fail("Implementation is missing.");
}

void Table::append(const std::vector<AllTypeVariant>& values) {
  // Implementation goes here
  Fail("Implementation is missing.");
}

void Table::create_new_chunk() {
  // Implementation goes here
  Fail("Implementation is missing.");
}

ColumnCount Table::column_count() const {
  // Implementation goes here
  return ColumnCount{0};
}

ChunkOffset Table::row_count() const {
  // Implementation goes here
  return 0;
}

ChunkID Table::chunk_count() const {
  // Implementation goes here
  return ChunkID{0};
}

ColumnID Table::column_id_by_name(const std::string& column_name) const {
  // Implementation goes here
  return ColumnID{0};
}

ChunkOffset Table::target_chunk_size() const {
  // Implementation goes here
  return ChunkOffset{0};
}

const std::vector<std::string>& Table::column_names() const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

const std::string& Table::column_name(const ColumnID column_id) const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

const std::string& Table::column_type(const ColumnID column_id) const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

std::shared_ptr<Chunk> Table::get_chunk(ChunkID chunk_id) {
  // Implementation goes here
  Fail("Implementation is missing.");
}

std::shared_ptr<const Chunk> Table::get_chunk(ChunkID chunk_id) const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

void Table::compress_chunk(const ChunkID chunk_id) {
  // Implementation goes here
  Fail("Implementation is missing.");
}

}  // namespace opossum
