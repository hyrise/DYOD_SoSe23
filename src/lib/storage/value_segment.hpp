#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "abstract_segment.hpp"

namespace opossum {

// ValueSegment is a segment type that stores all its values in a vector.
template <typename T>
class ValueSegment : public AbstractSegment {
 public:
  // Return the value at a certain position. If you want to write efficient operators, back off!
  AllTypeVariant operator[](const ChunkOffset chunk_offset) const final;

  // Add a value to the end.
  void append(const AllTypeVariant& val) final;

  // Return the number of entries.
  ChunkOffset size() const final;

  // Return all values. This is the preferred method to check a value at a certain index. Usually you need to
  // access more than a single value anyway.
  // e.g. const auto& values = value_segment.values(); and then: values[i]; in your loop.
  const std::vector<T>& values() const;

  // Returns the calculated memory usage.
  size_t estimate_memory_usage() const final;

 protected:
  // Implementation goes here
};

}  // namespace opossum
