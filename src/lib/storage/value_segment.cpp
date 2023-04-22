#include "value_segment.hpp"

#include "type_cast.hpp"
#include "utils/assert.hpp"

namespace opossum {

template <typename T>
ValueSegment<T>::ValueSegment(bool nullable) {
  // Implementation goes here
  _entries = std::vector<T>();
  _is_null_entries = std::vector<bool>();
  _nullable = nullable;
}

template <typename T>
AllTypeVariant ValueSegment<T>::operator[](const ChunkOffset chunk_offset) const {
  if(_is_null_entries[chunk_offset]){
    return NULL_VALUE;
  } else {
    return _entries[chunk_offset];
  }
}

template <typename T>
bool ValueSegment<T>::is_null(const ChunkOffset chunk_offset) const {
  return _is_null_entries[chunk_offset];
}

template <typename T>
T ValueSegment<T>::get(const ChunkOffset chunk_offset) const {
  if(_is_null_entries[chunk_offset]){
    throw std::logic_error("Value is null");
  }
  return _entries[chunk_offset];
}

template <typename T>
std::optional<T> ValueSegment<T>::get_typed_value(const ChunkOffset chunk_offset) const {
  if(_is_null_entries[chunk_offset]){
    return std::nullopt;
  } else {
    return _entries[chunk_offset];
  }
}

template <typename T>
void ValueSegment<T>::append(const AllTypeVariant& value) {
  if(variant_is_null(value)){
    if(!_nullable){
      throw std::logic_error("Segment is not nullable");
    } else {
      _entries.push_back(type_cast<T>(0));
      _is_null_entries.emplace_back(true);
      return;
    }
  }
  // TODO how to handle different type?
/*  std::cout << value << " " << sizeof(value) << std::endl;
  if(!_entries.empty() && sizeof(_entries) != sizeof(value)){
    throw std::logic_error("Wrong type passed");
  }*/
  // Todo: what to do if bigger (f.e. float in int segment) type is passed? Create entire segment again with different type?
  _entries.push_back(type_cast<T>(value));
  _is_null_entries.emplace_back(false);

}

template <typename T>
ChunkOffset ValueSegment<T>::size() const {
  return _entries.size();
}

template <typename T>
const std::vector<T>& ValueSegment<T>::values() const {
  return _entries;
}

template <typename T>
bool ValueSegment<T>::is_nullable() const {
  return _nullable;
}

template <typename T>
const std::vector<bool>& ValueSegment<T>::null_values() const {
  return _is_null_entries;
}

template <typename T>
size_t ValueSegment<T>::estimate_memory_usage() const {
  // Implementation goes here
  return _entries.capacity() * sizeof(T);
}

// Macro to instantiate the following classes:
// template class ValueSegment<int32_t>;
// template class ValueSegment<int64_t>;
// template class ValueSegment<float>;
// template class ValueSegment<double>;
// template class ValueSegment<std::string>;
EXPLICITLY_INSTANTIATE_DATA_TYPES(ValueSegment);

}  // namespace opossum
