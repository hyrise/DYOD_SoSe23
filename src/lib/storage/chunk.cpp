#include "chunk.hpp"

#include "abstract_segment.hpp"
#include "utils/assert.hpp"

namespace opossum {

void Chunk::add_segment(const std::shared_ptr<AbstractSegment> segment) {
  // Implementation goes here
}

void Chunk::append(const std::vector<AllTypeVariant>& values) {
  // Implementation goes here
}

std::shared_ptr<AbstractSegment> Chunk::get_segment(const ColumnID column_id) const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

ColumnCount Chunk::column_count() const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

ChunkOffset Chunk::size() const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

}  // namespace opossum
