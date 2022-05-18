#pragma once

#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "abstract_segment.hpp"
#include "dictionary_segment.hpp"
#include "table.hpp"
#include "types.hpp"
#include "utils/assert.hpp"
#include "value_segment.hpp"

namespace opossum {

// ReferenceSegment is a specific segment type that stores all its values as position list of a referenced column.
class ReferenceSegment : public AbstractSegment {
 public:
  // Creates a reference segment. The parameters specify the positions and the referenced column.
  ReferenceSegment(const std::shared_ptr<const Table>& referenced_table, const ColumnID referenced_column_id,
                   const std::shared_ptr<const PosList>& pos) {
    // TODO(student) implement it in a source file and change this to a declaration.
  }

  AllTypeVariant operator[](const ChunkOffset chunk_offset) const override {
    // TODO(student) implement it in a source file and change this to a declaration.
    return AllTypeVariant{};
  }

  void append(const AllTypeVariant&) override { throw std::logic_error("ReferenceSegment is immutable"); }

  ChunkOffset size() const override {
    // TODO(student) implement it in a source file and change this to a declaration.
    throw std::logic_error("ReferenceSegment is not implemented yet.");
  }

  const std::shared_ptr<const PosList>& pos_list() const {
    // TODO(student) implement it in a source file and change this to a declaration.
    throw std::logic_error("ReferenceSegment is not implemented yet.");
  }

  const std::shared_ptr<const Table>& referenced_table() const {
    // TODO(student) implement it in a source file and change this to a declaration.
    throw std::logic_error("ReferenceSegment is not implemented yet.");
  }

  ColumnID referenced_column_id() const {
    // TODO(student) implement it in a source file and change this to a declaration.
    throw std::logic_error("ReferenceSegment is not implemented yet.");
  }

  size_t estimate_memory_usage() const final {
    // TODO(student) implement it in a source file and change this to a declaration.
    throw std::logic_error("ReferenceSegment is not implemented yet.");
  }
};

}  // namespace opossum
