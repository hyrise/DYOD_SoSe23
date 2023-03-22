#include "table.hpp"

#include "utils/assert.hpp"

namespace opossum {

Table::Table(const ChunkOffset target_chunk_size) {
  // Implementation goes here
}

void Table::add_column_definition(const std::string& name, const std::string& type, const bool nullable) {
  // Implementation goes here
}

void Table::add_column(const std::string& name, const std::string& type, const bool nullable) {
  // Implementation goes here
  Fail("Implementation is missing.");
}

void Table::create_new_chunk() {
  // Implementation goes here
}

void Table::append(const std::vector<AllTypeVariant>& values) {
  // Implementation goes here
  Fail("Implementation is missing.");
}

ColumnCount Table::column_count() const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

uint64_t Table::row_count() const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

ChunkID Table::chunk_count() const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

ColumnID Table::column_id_by_name(const std::string& column_name) const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

ChunkOffset Table::target_chunk_size() const {
  // Implementation goes here
  Fail("Implementation is missing.");
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

bool Table::column_nullable(const ColumnID column_id) const {
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
