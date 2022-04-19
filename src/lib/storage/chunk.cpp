#include <iomanip>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "abstract_segment.hpp"
#include "chunk.hpp"

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
  return nullptr;
}

ColumnCount Chunk::column_count() const {
  // Implementation goes here
  return ColumnCount{0};
}

ChunkOffset Chunk::size() const {
  // Implementation goes here
  return 0;
}

}  // namespace opossum
