#include <memory>

#include "base_test.hpp"
#include "gtest/gtest.h"

#include "operators/get_table.hpp"
#include "storage/storage_manager.hpp"
#include "storage/table.hpp"

namespace opossum {
class OperatorsGetTableTest : public BaseTest {
 protected:
  void SetUp() override {
    _test_table = std::make_shared<Table>(2);
    StorageManager::get().add_table("TableA", _test_table);
  }

  std::shared_ptr<Table> _test_table;
};

TEST_F(OperatorsGetTableTest, GetOutput) {
  auto get_table_oper = std::make_shared<GetTable>("TableA");
  get_table_oper->execute();

  EXPECT_EQ(get_table_oper->get_output(), _test_table);
}

TEST_F(OperatorsGetTableTest, ThrowsUnknownTableName) {
  auto get_table_oper = std::make_shared<GetTable>("TableB");

  EXPECT_THROW(get_table_oper->execute(), std::exception) << "Should throw unknown table name exception";
}

}  // namespace opossum
