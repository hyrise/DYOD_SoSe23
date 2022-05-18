#pragma once

#include <memory>
#include <string>

#include "all_type_variant.hpp"
#include "types.hpp"

namespace opossum {

// AbstractSegment is the abstract super class for all segment types,
// e.g., ValueSegment, ReferenceSegment
class AbstractSegment : private Noncopyable {
 public:
  AbstractSegment() = default;
  virtual ~AbstractSegment() = default;

  // We need to explicitly set the move constructor to default when we overwrite the copy constructor.
  AbstractSegment(AbstractSegment&&) = default;

  AbstractSegment& operator=(AbstractSegment&&) = default;

  // Returns the value at a given position.
  virtual AllTypeVariant operator[](const ChunkOffset chunk_offset) const {
    // TODO(student) Remove this implementation since it should be pure virtual. Currently, it's implemented to
    // successfully compile the tests.
    return AllTypeVariant{};
  }

  // Appends the value at the end of the segment.
  virtual void append(const AllTypeVariant& val) {
    // TODO(student) Remove this implementation since it should be pure virtual. Currently, it's implemented to
    // successfully compile the tests.
  }

  // Returns the number of values.
  virtual ChunkOffset size() const {
    // TODO(student) Remove this implementation since it should be pure virtual. Currently, it's implemented to
    // successfully compile the tests.
    return ChunkOffset{};
  }

  // Returns the calculated memory usage.
  virtual size_t estimate_memory_usage() const {
    // TODO(student) Remove this implementation since it should be pure virtual. Currently, it's implemented to
    // successfully compile the tests.
    return size_t{};
  }
};

}  // namespace opossum
