#include "gtest/gtest.h"

#include "BigInt.h"

TEST(BigInt, ShouldBeEqual) {
  EXPECT_TRUE(BigInt(1) == BigInt(1));
  EXPECT_FALSE(BigInt(1) != BigInt(1));
}

TEST(BigInt, ShouldNotBeEqual) {
  EXPECT_TRUE(BigInt(1) != BigInt(2));
  EXPECT_FALSE(BigInt(1) == BigInt(2));
}

TEST(BigInt, ShouldAddOneAndTwo) {
  EXPECT_EQ(BigInt(3), BigInt(1) + BigInt(2));
}

TEST(BigInt, ShouldSupportBigIntegers) {
  EXPECT_NO_THROW(BigInt(1000000000000000000));
}

TEST(BigInt, ShouldOutputToStreams) {
  ostringstream oss;
  oss << BigInt(1000000000000000000);
  EXPECT_EQ(std::string("1000000000000000000"), oss.str());
}

TEST(BigInt, ShouldAddBigIntegers) {
  EXPECT_EQ(BigInt(2000000000000000000), BigInt(1000000000000000000) + BigInt(1000000000000000000));
}

