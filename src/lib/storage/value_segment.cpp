#include "value_segment.hpp"

#include "type_cast.hpp"
#include "utils/assert.hpp"

namespace opossum {

template <typename T>
ValueSegment<T>::ValueSegment(bool nullable) {
  if (nullable) {
    null_values_ = std::vector<bool>();
  }
}

template <typename T>
AllTypeVariant ValueSegment<T>::operator[](const ChunkOffset chunk_offset) const {
  DebugAssert(chunk_offset < size(), "Out of bounds.");
  if (is_nullable() && (*null_values_)[chunk_offset]) {
    return NULL_VALUE;
  }
  return values_.at(chunk_offset);
}

template <typename T>
bool ValueSegment<T>::is_null(const ChunkOffset chunk_offset) const {
  DebugAssert(chunk_offset < size(), "Out of bounds.");
  return is_nullable() && (*null_values_)[chunk_offset];
}

template <typename T>
T ValueSegment<T>::get(const ChunkOffset chunk_offset) const {
  DebugAssert(chunk_offset < size(), "Out of bounds.");
  if (is_nullable() && (*null_values_)[chunk_offset]) {
    throw std::logic_error("NULL value at chunk_offset.");
  }
  return values_[chunk_offset];
}

template <typename T>
std::optional<T> ValueSegment<T>::get_typed_value(const ChunkOffset chunk_offset) const {
  DebugAssert(chunk_offset < size(), "Out of bounds.");
  if (is_nullable() && (*null_values_)[chunk_offset]) {
    return std::nullopt;
  }
  return values_[chunk_offset];
}

template <typename T>
void ValueSegment<T>::append(const AllTypeVariant& value) {
  if (variant_is_null(value)) {
    if (!is_nullable()) {
      throw std::logic_error("Trying to append NULL value to non nullable segment.");
    }
    (*null_values_).push_back(variant_is_null(value));
    values_.push_back(T{});
    return;
  }
  try {
    values_.push_back(type_cast<T>(value));
    if (is_nullable()) {
      (*null_values_).push_back(false);
    }
  } catch (...) {
    throw std::logic_error("Could not cast value to segment's type.");
  }
}

template <typename T>
ChunkOffset ValueSegment<T>::size() const {
  return values_.size();
}

template <typename T>
const std::vector<T>& ValueSegment<T>::values() const {
  return values_;
}

template <typename T>
bool ValueSegment<T>::is_nullable() const {
  return static_cast<bool>(null_values_);
}

template <typename T>
const std::vector<bool>& ValueSegment<T>::null_values() const {
  if (!is_nullable()) {
    throw std::logic_error("Segment is not nullable.");
  }
  return *null_values_;
}

template <typename T>
size_t ValueSegment<T>::estimate_memory_usage() const {
  return values_.capacity() * sizeof(T);
}

// Macro to instantiate the following classes:
// template class ValueSegment<int32_t>;
// template class ValueSegment<int64_t>;
// template class ValueSegment<float>;
// template class ValueSegment<double>;
// template class ValueSegment<std::string>;
EXPLICITLY_INSTANTIATE_DATA_TYPES(ValueSegment);

}  // namespace opossum