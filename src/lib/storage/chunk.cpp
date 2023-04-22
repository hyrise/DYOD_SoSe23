#include "chunk.hpp"

#include "abstract_segment.hpp"
#include "utils/assert.hpp"

namespace opossum {

void Chunk::add_segment(const std::shared_ptr<AbstractSegment> segment) {
  _segments.emplace_back(segment);
}

void Chunk::append(const std::vector<AllTypeVariant>& values) {
  DebugAssert(
      values.size()==_segments.size(),
      "Different amount of values compared to columns."
  );
  for(auto index = size_t{0}; index < values.size(); index++){
    auto segment = _segments.at(index);
    segment->append(values.at(index));
  }
}

std::shared_ptr<AbstractSegment> Chunk::get_segment(const ColumnID column_id) const {
  return _segments.at(column_id);
}

ColumnCount Chunk::column_count() const {
  return ColumnCount{_segments.size()};
}

ChunkOffset Chunk::size() const {
  return _segments.size() ? _segments[0]->size() : 0;
}

}  // namespace opossum
