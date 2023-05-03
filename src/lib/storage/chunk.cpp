#include "chunk.hpp"

#include "utils/assert.hpp"

namespace opossum {

void Chunk::add_segment(const std::shared_ptr<AbstractSegment> segment) {
  // Implementation goes here
  _columns.push_back(segment);
}

template <typename T>
bool append_with_type(std::vector<std::shared_ptr<AbstractSegment>>::iterator column_it,
                      std::vector<AllTypeVariant>::const_iterator value_it) {
  auto segment = std::dynamic_pointer_cast<ValueSegment<T>>(*column_it);
  if (segment) {
    segment->append(*value_it);
    return true;
  }
  return false;
}

void Chunk::append(const std::vector<AllTypeVariant>& values) {
  // Implementation goes here
  DebugAssert(values.size() == column_count(), "Cannot insert a tuple with less values than columns.");

  // Problem: How to iterate over the given data types in all_type_variant?
  const auto no_types = types.storage_.size_;
  DebugAssert(no_types == 5, "There are 5 supported data types but a different count was found.");

  auto column_it = _columns.begin();
  auto value_it = values.begin();

  for (; column_it < _columns.end(); ++column_it) {

    (append_with_type<int32_t>(column_it, value_it) || append_with_type<int64_t>(column_it, value_it) ||
     append_with_type<float>(column_it, value_it) || append_with_type<double>(column_it, value_it) ||
     append_with_type<std::string>(column_it, value_it));

    ++value_it;
  }
}

std::shared_ptr<AbstractSegment> Chunk::get_segment(const ColumnID column_id) const {
  return _columns[column_id];
}

ColumnCount Chunk::column_count() const {
  return static_cast<ColumnCount>(_columns.size());
}

ChunkOffset Chunk::size() const {
  if (_columns.size() == 0)
    return ChunkOffset{0};
  return static_cast<ChunkOffset>((*_columns[0]).size());
}

}  // namespace opossum
