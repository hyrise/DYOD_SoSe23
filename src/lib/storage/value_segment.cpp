#include "value_segment.hpp"

#include "type_cast.hpp"
#include "utils/assert.hpp"

namespace opossum {

template <typename T>
ValueSegment<T>::ValueSegment(bool nullable) {
  // Implementation goes here
}

template <typename T>
AllTypeVariant ValueSegment<T>::operator[](const ChunkOffset chunk_offset) const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

template <typename T>
bool ValueSegment<T>::is_null(const ChunkOffset chunk_offset) const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

template <typename T>
T ValueSegment<T>::get(const ChunkOffset chunk_offset) const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

template <typename T>
std::optional<T> ValueSegment<T>::get_typed_value(const ChunkOffset chunk_offset) const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

template <typename T>
void ValueSegment<T>::append(const AllTypeVariant& value) {
  // Implementation goes here
  Fail("Implementation is missing.");
}

template <typename T>
ChunkOffset ValueSegment<T>::size() const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

template <typename T>
const std::vector<T>& ValueSegment<T>::values() const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

template <typename T>
bool ValueSegment<T>::is_nullable() const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

template <typename T>
const std::vector<bool>& ValueSegment<T>::null_values() const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

template <typename T>
size_t ValueSegment<T>::estimate_memory_usage() const {
  // Implementation goes here
  Fail("Implementation is missing.");
}

// Macro to instantiate the following classes:
// template class ValueSegment<int32_t>;
// template class ValueSegment<int64_t>;
// template class ValueSegment<float>;
// template class ValueSegment<double>;
// template class ValueSegment<std::string>;
EXPLICITLY_INSTANTIATE_DATA_TYPES(ValueSegment);

}  // namespace opossum
