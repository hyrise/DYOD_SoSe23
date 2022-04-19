#pragma once

#include <iostream>

#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_empty.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <boost/type_traits/is_stateless.hpp>

namespace opossum {

/**
 * @brief Represents SQL NULL value in AllTypeVariant
 *
 * Based on boost/blank.hpp with changed relational operators
 */
struct NullValue {};

// Relational operators
inline bool operator==(const NullValue& /*lhs*/, const NullValue& /*rhs*/) {
  return false;
}

inline bool operator!=(const NullValue& /*lhs*/, const NullValue& /*rhs*/) {
  return false;
}

inline bool operator<(const NullValue& /*lhs*/, const NullValue& /*rhs*/) {
  return false;
}

inline bool operator<=(const NullValue& /*lhs*/, const NullValue& /*rhs*/) {
  return false;
}

inline bool operator>(const NullValue& /*lhs*/, const NullValue& /*rhs*/) {
  return false;
}

inline bool operator>=(const NullValue& /*lhs*/, const NullValue& /*rhs*/) {
  return false;
}

inline NullValue operator-(const NullValue& /*value*/) {
  return NullValue{};
}

inline std::ostream& operator<<(std::ostream& stream, const NullValue& /*value*/) {
  stream << "NULL";
  return stream;
}

}  // namespace opossum

namespace boost {
// Type traits specializations

template <>
struct is_pod<opossum::NullValue> : mpl::true_ {};

template <>
struct is_empty<opossum::NullValue> : mpl::true_ {};

template <>
struct is_stateless<opossum::NullValue> : mpl::true_ {};

}  // namespace boost
