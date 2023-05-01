#include "chunk.hpp"
#include "abstract_segment.hpp"
#include "utils/assert.hpp"
#include "value_segment.hpp"

namespace opossum {

void Chunk::add_segment(const std::shared_ptr<AbstractSegment> column) {
  // Implementation goes here
  _columns.push_back(column);
}

void Chunk::append(const std::vector<AllTypeVariant>& values) {
  // Implementation goes here
  Assert(values.size() == column_count(), "Cannot insert a tuple with less values than columns.");

  for (auto ind = uint32_t{0}; ind < values.size(); ++ind) {
    const auto segment = std::dynamic_pointer_cast<ValueSegment<AllTypeVariant>>(_columns[ind]);
    DebugAssert(segment, "Segment needs to be ValueSegment in order to cast to AbstractSegment");
    segment->append(values.at(ind));
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
  return static_cast<ChunkOffset>((*_columns[0]).size());
}

}  // namespace opossum
