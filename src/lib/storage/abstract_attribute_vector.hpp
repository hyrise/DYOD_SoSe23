#pragma once

#include "types.hpp"

namespace opossum {

// AbstractAttributeVector is the abstract super class for all attribute vectors,
// e.g., FixedWidthIntegerVector
class AbstractAttributeVector : private Noncopyable {
 public:
  AbstractAttributeVector() = default;
  virtual ~AbstractAttributeVector() = default;

  // we need to explicitly set the move constructor to default when
  // we overwrite the copy constructor
  AbstractAttributeVector(AbstractAttributeVector&&) = default;
  AbstractAttributeVector& operator=(AbstractAttributeVector&&) = default;

  // returns the value id at a given position
  virtual ValueID get(const size_t index) const = 0;

  // sets the value id at a given position
  virtual void set(const size_t index, const ValueID value_id) = 0;

  // returns the number of values
  virtual size_t size() const = 0;

  // returns the width of biggest value id in bytes
  virtual AttributeVectorWidth width() const = 0;
};

}  // namespace opossum
