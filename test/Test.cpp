#include <gtest/gtest.h>
#include "../src/headers/Example.hpp"

TEST(TestSuiteSample, TestSample)
{
  EXPECT_EQ(sum(5, 2), 7);
  EXPECT_EQ(sum(0, 1), 1);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}