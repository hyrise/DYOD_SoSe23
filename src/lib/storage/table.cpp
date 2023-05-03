#include "table.hpp"
#include "resolve_type.hpp"
#include "utils/assert.hpp"

namespace opossum {

Table::Table(const ChunkOffset target_chunk_size) {
  _target_chunk_size = target_chunk_size;
  _chunks = std::vector<std::shared_ptr<Chunk>>{std::make_shared<Chunk>()};
}

void Table::add_column_definition(const std::string& name, const std::string& type, const bool nullable) {
  DebugAssert(_column_names.size() == _column_types.size() && _column_types.size() == _column_nullable.size(),
              "Columns are not well defined");
  if (std::find(_column_names.begin(), _column_names.end(), name) != _column_names.end()) {
    throw std::logic_error("It is not allowed to add two columns with the same name.");
  }

  _column_names.emplace_back(name);
  _column_types.emplace_back(type);
  _column_nullable.emplace_back(nullable);
}

void Table::add_column(const std::string& name, const std::string& type, const bool nullable) {
  DebugAssert(_chunks[0]->size() == 0, "Adding columns is only allowed if the table does not have any entries.");
  add_column_definition(name, type, nullable);
  resolve_data_type(type, [&](const auto data_type_t) {
    using ColumnDataType = typename decltype(data_type_t)::type;
    const auto value_segment = std::make_shared<ValueSegment<ColumnDataType>>(nullable);
    _chunks[0]->add_segment(value_segment);
  });
}

void Table::create_new_chunk() {
  if (_chunks.back()->size() < _target_chunk_size) {
    throw std::logic_error("It is not allowed to add a new chunk if the last chunk is not full yet.");
  }

  _chunks.emplace_back(std::make_shared<Chunk>());

  size_t num_columns = _column_types.size();
  for (unsigned int col_id = 0; col_id < num_columns; ++col_id) {
    resolve_data_type(_column_types[col_id], [&](const auto data_type_t) {
      using ColumnDataType = typename decltype(data_type_t)::type;
      const auto value_segment = std::make_shared<ValueSegment<ColumnDataType>>(_column_nullable[col_id]);
      _chunks.back()->add_segment(value_segment);
    });
  }
}

void Table::append(const std::vector<AllTypeVariant>& values) {
  if (_chunks.back()->size() == _target_chunk_size) {
    create_new_chunk();
  }
  _chunks.back()->append(values);
}

ColumnCount Table::column_count() const {
  return static_cast<ColumnCount>(_column_names.size());
}

uint64_t Table::row_count() const {
  // This is based on the assumption that all but the last chunk contain exactly _target_chunk_size values.
  return (chunk_count() - 1) * _target_chunk_size + _chunks.back()->size();
}

ChunkID Table::chunk_count() const {
  return static_cast<ChunkID>(_chunks.size());
}

ColumnID Table::column_id_by_name(const std::string& column_name) const {
  size_t num_columns = _column_names.size();
  for (uint16_t col_id = 0; col_id < num_columns; ++col_id) {
    if (_column_names[col_id] == column_name) {
      return ColumnID{col_id};
    }
  }
  throw std::logic_error("Table does not contain column with the requested name.");
}

ChunkOffset Table::target_chunk_size() const {
  return _target_chunk_size;
}

const std::vector<std::string>& Table::column_names() const {
  return _column_names;
}

const std::string& Table::column_name(const ColumnID column_id) const {
  if (column_id > _column_names.size()) {
    throw std::logic_error("Table does not contain column with the requested id.");
  }
  return _column_names[column_id];
}

const std::string& Table::column_type(const ColumnID column_id) const {
  if (column_id > _column_types.size()) {
    throw std::logic_error("Table does not contain column with the requested id.");
  }
  return _column_types[column_id];
}

bool Table::column_nullable(const ColumnID column_id) const {
  if (column_id > _column_nullable.size()) {
    throw std::logic_error("Table does not contain column with the requested id.");
  }
  return _column_nullable[column_id];
}

std::shared_ptr<Chunk> Table::get_chunk(ChunkID chunk_id) {
  if (chunk_id >= static_cast<ChunkID>(_chunks.size())) {
    throw std::logic_error("Table does not contain chunk with the requested id.");
  }
  return _chunks[chunk_id];
}

std::shared_ptr<const Chunk> Table::get_chunk(ChunkID chunk_id) const {
  if (chunk_id >= static_cast<ChunkID>(_chunks.size())) {
    throw std::logic_error("Table does not contain chunk with the requested id.");
  }
  return _chunks[chunk_id];
}

void Table::compress_chunk(const ChunkID chunk_id) {
  // Implementation goes here
  Fail("Implementation is missing.");
}

}  // namespace opossum
