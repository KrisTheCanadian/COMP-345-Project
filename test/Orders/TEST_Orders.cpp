#include <gtest/gtest.h>
#include "Orders/Orders.h"

TEST(OrdersListSuite, listInitialized)
{
  // arrange
  OrdersList list;
  // act
  list = OrdersList();
  // assert
  auto orders = list.getList();
  EXPECT_EQ(orders->size(), 0);
}

TEST(OrdersListSuite, listAddOrders)
{
  // arrange
  OrdersList list{};
  // act
  list.add(UserInputOrder::create("Deploy"));
  list.add(UserInputOrder::create("Advance"));
  list.add(UserInputOrder::create("Bomb"));
  list.add(UserInputOrder::create("Blockade"));
  list.add(UserInputOrder::create("Airlift"));
  list.add(UserInputOrder::create("Negotiate"));
  // assert
  auto orders = list.getList();
  EXPECT_EQ(orders->size(), 6);
}

TEST(OrdersListSuite, listRemoveOrder)
{
  // arrange
  OrdersList list{};
  // act
  list.add(UserInputOrder::create("Deploy"));
  list.add(UserInputOrder::create("Advance"));
  list.add(UserInputOrder::create("Airlift"));
  list.remove(0);
  // assert
  auto orders = list.getList();

  EXPECT_EQ(orders->size(), 2);
  EXPECT_EQ(orders->at(0)->getLabel(), "Advance");
  EXPECT_EQ(orders->at(1)->getLabel(), "Airlift");
}

TEST(OrdersListSuite, listExecuteOrder)
{
  // arrange
  OrdersList list{};
  // act
  list.add(UserInputOrder::create("Deploy"));
  list.add(UserInputOrder::create("Advance"));
  list.add(UserInputOrder::create("Airlift"));
  list.execute();

  auto orders = list.getList();
  // assert
  EXPECT_EQ(orders->size(), 0);
}

TEST(OrdersListSuite, listMoveOrder)
{
  // arrange
  OrdersList list{};
  // act
  list.add(UserInputOrder::create("Deploy"));
  list.add(UserInputOrder::create("Advance"));
  list.add(UserInputOrder::create("Airlift"));
  list.add(UserInputOrder::create("Bomb"));

  list.move(2, 0);

  auto orders = list.getList();
  // assert
  EXPECT_EQ(orders->size(), 4);
  EXPECT_EQ(orders->at(0)->getLabel(), "Airlift");
  EXPECT_EQ(orders->at(2)->getLabel(), "Deploy");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
