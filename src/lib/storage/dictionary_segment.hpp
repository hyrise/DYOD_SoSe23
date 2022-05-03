#pragma once

#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "abstract_segment.hpp"
#include "all_type_variant.hpp"
#include "types.hpp"

namespace opossum {

class AbstractAttributeVector;

// Even though ValueIDs do not have to use the full width of ValueID (uint32_t), this will also work for smaller ValueID
// types (uint8_t, uint16_t) since after a down-cast INVALID_VALUE_ID will look like their numeric_limit::max().
constexpr ValueID INVALID_VALUE_ID{std::numeric_limits<ValueID::base_type>::max()};

// Dictionary is a specific segment type that stores all its values in a vector
template <typename T>
class DictionarySegment : public AbstractSegment {
 public:
  /**
   * Creates a Dictionary segment from a given value segment.
   */
  explicit DictionarySegment(const std::shared_ptr<AbstractSegment>& abstract_segment);

  // Return the value at a certain position. If you want to write efficient operators, back off!
  AllTypeVariant operator[](const ChunkOffset chunk_offset) const override;

  // Return the value at a certain position.
  T get(const ChunkOffset chunk_offset) const;

  // Dictionary segments are immutable.
  void append(const AllTypeVariant& value) override;

  // Returns an underlying dictionary.
  const std::vector<T>& dictionary() const;

  // Returns an underlying data structure.
  std::shared_ptr<const AbstractAttributeVector> attribute_vector() const;

  // Return the value represented by a given ValueID.
  const T value_of_value_id(const ValueID value_id) const;

  // Returns the first value ID that refers to a value >= the search value. Returns INVALID_VALUE_ID if all values are
  // smaller than the search value.
  ValueID lower_bound(const T value) const;

  // Same as lower_bound(T), but accepts an AllTypeVariant.
  ValueID lower_bound(const AllTypeVariant& value) const;

  // Returns the first value ID that refers to a value > the search value. Returns INVALID_VALUE_ID if all values are
  // smaller than or equal to the search value.
  ValueID upper_bound(const T value) const;

  // Same as upper_bound(T), but accepts an AllTypeVariant.
  ValueID upper_bound(const AllTypeVariant& value) const;

  // Return the number of unique_values (dictionary entries).
  ChunkOffset unique_values_count() const;

  // Return the number of entries.
  ChunkOffset size() const override;

  // Returns the calculated memory usage.
  size_t estimate_memory_usage() const final;

 protected:
  std::vector<T> _dictionary;
  std::shared_ptr<AbstractAttributeVector> _attribute_vector;
};

}  // namespace opossum
