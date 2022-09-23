#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MapLoader.h"

TEST(TestSuiteSample, TestSample)
{
    // arrange
    MapLoader loader;

    // act
    Map* map = loader.load("../res/Test.map");

    std::string map_name = map->getName();
    // assert
    EXPECT_EQ(map_name, "Test.map");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}