#include "chunk.hpp"

#include "utils/assert.hpp"

namespace opossum {

void Chunk::add_segment(const std::shared_ptr<AbstractSegment> column) {
  // Implementation goes here
  _columns.push_back(column);
}

void Chunk::append(const std::vector<AllTypeVariant>& values) {
  // Implementation goes here
  DebugAssert(values.size() == column_count(), "Cannot insert a tuple with less values than columns.");

  auto column_it = _columns.begin();
  auto value_it = values.begin();

  while (column_it != _columns.end()) {
    // Still very ugly.
    // TODO(Robert): Find a way to iterate over the available data types in all_type_variant

    bool success = false;
    auto s1 = std::dynamic_pointer_cast<ValueSegment<int32_t>>(*column_it);
    if (s1) {
      s1->append(*value_it);
      success = true;
    }

    auto s2 = std::dynamic_pointer_cast<ValueSegment<int64_t>>(*column_it);
    if (!success && s2) {
      s2->append(*value_it);
      success = true;
    }

    auto s3 = std::dynamic_pointer_cast<ValueSegment<float>>(*column_it);
    if (!success && s3) {
      s3->append(*value_it);
      success = true;
    }

    auto s4 = std::dynamic_pointer_cast<ValueSegment<double>>(*column_it);
    if (!success && s4) {
      s4->append(*value_it);
      success = true;
    }

    auto s5 = std::dynamic_pointer_cast<ValueSegment<std::string>>(*column_it);
    if (!success && s5) {
      s5->append(*value_it);
      success = true;
    }

    DebugAssert(success, "Only ValueSegments can be appended to chunks.");

    ++column_it;
    ++value_it;
  }
}

std::shared_ptr<AbstractSegment> Chunk::get_segment(const ColumnID column_id) const {
  // Implementation goes here
  return _columns[column_id];
}

ColumnCount Chunk::column_count() const {
  // Implementation goes here
  return static_cast<ColumnCount>(_columns.size());
}

ChunkOffset Chunk::size() const {
  // Implementation goes here
  if (_columns.size() == 0)
    return ChunkOffset{0};
  return static_cast<ChunkOffset>((*_columns[0]).size());
}

}  // namespace opossum
