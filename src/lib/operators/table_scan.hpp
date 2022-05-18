#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "abstract_operator.hpp"
#include "all_type_variant.hpp"
#include "types.hpp"
#include "utils/assert.hpp"

namespace opossum {

class BaseTableScanImpl;
class Table;

class TableScan : public AbstractOperator {
 public:
  TableScan(const std::shared_ptr<const AbstractOperator>& in, const ColumnID column_id, const ScanType scan_type,
            const AllTypeVariant search_value) {
    // TODO(student) implement it in a source file and change this to a declaration.
  }

  ColumnID column_id() const {
    // TODO(student) implement it in a source file and change this to a declaration.
    return ColumnID{};
  }

  ScanType scan_type() const {
    // TODO(student) implement it in a source file and change this to a declaration.
    Fail("Implementation missing.");
  }

  const AllTypeVariant& search_value() const {
    // TODO(student) implement it in a source file and change this to a declaration.
    Fail("Implementation missing.");
  }

 protected:
  std::shared_ptr<const Table> _on_execute() override {
    // TODO(student) implement it in a source file and change this to a declaration.
    Fail("Implementation missing.");
  }
};

}  // namespace opossum
