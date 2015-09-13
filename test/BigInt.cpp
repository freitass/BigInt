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

//int main(int, char**) {
//  cout << BigInt(1) + BigInt(2) << endl;
//  cout << BigInt(1000000000000000000) << endl;
//  cout << BigInt(1000000000000000000) + BigInt(1000000000000000000) << endl;
//  cout << boolalpha << (BigInt(1000000000000000000) == BigInt(2000000000000000000)) << endl;
//  cout << boolalpha << (BigInt(2000000000000000000) == BigInt(2000000000000000000)) << endl;
//  //cout << BigInt(10000000000000000000) * BigInt(2) << endl;
//  return 0;
//}

