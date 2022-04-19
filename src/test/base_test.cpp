#include "base_test.hpp"

#include "storage/storage_manager.hpp"
#include "type_cast.hpp"

namespace opossum {

void BaseTest::EXPECT_TABLE_EQ(const Table& tleft, const Table& tright, bool order_sensitive, bool strict_types) {
  EXPECT_TRUE(_table_equal(tleft, tright, order_sensitive, strict_types));
}

void BaseTest::ASSERT_TABLE_EQ(const Table& tleft, const Table& tright, bool order_sensitive, bool strict_types) {
  ASSERT_TRUE(_table_equal(tleft, tright, order_sensitive, strict_types));
}

void BaseTest::EXPECT_TABLE_EQ(std::shared_ptr<const Table> tleft, std::shared_ptr<const Table> tright,
                               bool order_sensitive, bool strict_types) {
  EXPECT_TABLE_EQ(*tleft, *tright, order_sensitive, strict_types);
}

void BaseTest::ASSERT_TABLE_EQ(std::shared_ptr<const Table> tleft, std::shared_ptr<const Table> tright,
                               bool order_sensitive, bool strict_types) {
  ASSERT_TABLE_EQ(*tleft, *tright, order_sensitive, strict_types);
}

BaseTest::Matrix BaseTest::_table_to_matrix(const Table& table) {
  // Initialize matrix with table sizes.
  auto matrix = Matrix(table.row_count(), std::vector<AllTypeVariant>(table.column_count()));

  // Set values.
  auto row_offset = uint64_t{0};
  for (auto chunk_id = ChunkID{0}; chunk_id < table.chunk_count(); ++chunk_id) {
    const auto chunk = table.get_chunk(chunk_id);

    // An empty table's chunk might be missing actual segments.
    if (chunk->size() == 0) {
      continue;
    }

    for (auto column_id = ColumnID{0}; column_id < table.column_count(); ++column_id) {
      const auto segment = chunk->get_segment(column_id);

      for (auto chunk_offset = ChunkOffset{0}; chunk_offset < chunk->size(); ++chunk_offset) {
        matrix[row_offset + chunk_offset][column_id] = (*segment)[chunk_offset];
      }
    }
    row_offset += chunk->size();
  }

  return matrix;
}

void BaseTest::_print_matrix(const BaseTest::Matrix& matrix) {
  std::cout << "-------------" << std::endl;
  for (auto row = uint64_t{0}; row < matrix.size(); ++row) {
    for (auto column = ColumnID{0}; column < matrix[row].size(); ++column) {
      std::cout << std::setw(8) << matrix[row][column] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "-------------" << std::endl;
}

::testing::AssertionResult BaseTest::_table_equal(const Table& tleft, const Table& tright, bool order_sensitive,
                                                  bool strict_types) {
  auto left = _table_to_matrix(tleft);
  auto right = _table_to_matrix(tright);
  // compare schema of tables
  //  - column count
  if (tleft.column_count() != tright.column_count()) {
    _print_matrix(left);
    _print_matrix(right);
    return ::testing::AssertionFailure() << "Number of columns is different.";
  }

  //  - column names and types
  for (auto column_id = ColumnID{0}; column_id < tright.column_count(); ++column_id) {
    auto left_data_type = tleft.column_type(column_id);
    auto right_data_type = tright.column_type(column_id);
    // This is needed for the SQLiteTestrunner, since SQLite does not differentiate between float/double, and int/long.
    if (!strict_types) {
      if (left_data_type == "double") {
        left_data_type = "float";
      } else if (left_data_type == "long") {
        left_data_type = "int";
      }

      if (right_data_type == "double") {
        right_data_type = "float";
      } else if (right_data_type == "long") {
        right_data_type = "int";
      }
    }
    if (left_data_type != right_data_type || tleft.column_name(column_id) != tright.column_name(column_id)) {
      std::cout << "Column with ID " << column_id << " is different" << std::endl;
      std::cout << "Got: " << tleft.column_name(column_id) << " (" << tleft.column_type(column_id) << ")" << std::endl;
      std::cout << "Expected: " << tright.column_name(column_id) << " (" << tright.column_type(column_id) << ")"
                << std::endl;
      return ::testing::AssertionFailure() << "Table schema is different.";
    }
  }

  // compare content of tables
  //  - row count for fast failure
  if (tleft.row_count() != tright.row_count()) {
    _print_matrix(left);
    _print_matrix(right);
    std::cout << "Got: " << tleft.row_count() << " rows" << std::endl;
    std::cout << "Expected: " << tright.row_count() << " rows" << std::endl;
    return ::testing::AssertionFailure() << "Number of rows is different.";
  }

  // sort if order does not matter
  if (!order_sensitive) {
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
  }

  for (auto row = uint64_t{0}; row < left.size(); ++row)
    for (auto column_id = ColumnID{0}; column_id < left[row].size(); ++column_id) {
      if (tleft.column_type(column_id) == "float") {
        const auto left_val = type_cast<float>(left[row][column_id]);
        const auto right_val = type_cast<float>(right[row][column_id]);

        if (strict_types) {
          EXPECT_EQ(tright.column_type(column_id), "float");
        } else {
          EXPECT_TRUE(tright.column_type(column_id) == "float" || tright.column_type(column_id) == "double");
        }
        EXPECT_NEAR(left_val, right_val, 0.0001) << "Row/Column:" << row << "/" << column_id;
      } else if (tleft.column_type(column_id) == "double") {
        const auto left_val = type_cast<double>(left[row][column_id]);
        const auto right_val = type_cast<double>(right[row][column_id]);

        if (strict_types) {
          EXPECT_EQ(tright.column_type(column_id), "double");
        } else {
          EXPECT_TRUE(tright.column_type(column_id) == "float" || tright.column_type(column_id) == "double");
        }
        EXPECT_NEAR(left_val, right_val, 0.0001) << "Row/Column:" << row << "/" << column_id;
      } else {
        if (!strict_types && (tleft.column_type(column_id) == "int" || tleft.column_type(column_id) == "long")) {
          const auto left_val = type_cast<int64_t>(left[row][column_id]);
          const auto right_val = type_cast<int64_t>(right[row][column_id]);
          EXPECT_EQ(left_val, right_val) << "Row:" << row + 1 << " Column_id:" << column_id + 1;
        } else {
          EXPECT_EQ(left[row][column_id], right[row][column_id]) << "Row:" << row + 1 << " Column:" << column_id + 1;
        }
      }
    }

  return ::testing::AssertionSuccess();
}

BaseTest::~BaseTest() {
  StorageManager::get().reset();
}

}  // namespace opossum
