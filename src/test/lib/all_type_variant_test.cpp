#include "base_test.hpp"

namespace opossum {

template <typename T>
class AllTypeVariantTest : public BaseTest {};

using AllTypeVariantTestDataTypes = ::testing::Types<int32_t, int64_t, float, double, std::string, NullValue>;
TYPED_TEST_SUITE(AllTypeVariantTest, AllTypeVariantTestDataTypes, );  // NOLINT(whitespace/parens)

TYPED_TEST(AllTypeVariantTest, GetExtractsExactValue) {
  auto values = std::vector<TypeParam>{};
  if constexpr (std::is_same_v<TypeParam, std::string>) {
    values.emplace_back(std::string{});
    values.emplace_back(std::string{"shortstring"});
    values.emplace_back(std::string{"reallyreallylongstringthatcantbestoredusingsso"});
  } else if constexpr (std::is_same_v<TypeParam, NullValue>) {
    values.emplace_back(NullValue{});
  } else {
    values.emplace_back(std::numeric_limits<TypeParam>::min());
    values.emplace_back(std::numeric_limits<TypeParam>::lowest());
    values.emplace_back(std::numeric_limits<TypeParam>::max());
    values.emplace_back(TypeParam{0});
    values.emplace_back(TypeParam{17});
  }

  for (const auto& value_in : values) {
    if constexpr (std::is_same_v<TypeParam, NullValue>) {
      const auto variant = AllTypeVariant{value_in};

      EXPECT_NE(variant, NULL_VALUE);
      EXPECT_TRUE(variant_is_null(variant));
    } else {
      const auto variant = AllTypeVariant{value_in};
      const auto value_out = boost::get<TypeParam>(variant);

      EXPECT_EQ(value_in, value_out);
      EXPECT_FALSE(variant_is_null(variant));
    }
  }
}

}  // namespace opossum
