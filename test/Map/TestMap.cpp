#include <gtest/gtest.h>

TEST(TestSuiteSample, TestSample)
{
    EXPECT_EQ(7, 7);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}