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
    Deploy *deploy = new Deploy();
    Advance *advance = new Advance();
    Bomb *bomb = new Bomb();
    Blockade *blockade = new Blockade();
    Airlift *airlift = new Airlift();
    Negotiate *negotiate = new Negotiate();

  list.add(deploy);
  list.add(advance);
  list.add(bomb);
  list.add(blockade);
  list.add(airlift);
  list.add(negotiate);
  // assert
  auto orders = list.getList();
  EXPECT_EQ(orders->size(), 6);
}

TEST(OrdersListSuite, listRemoveOrder)
{
  // arrange
  OrdersList list{};
  // act
    Deploy *deploy = new Deploy();
    Advance *advance = new Advance();
    Bomb *bomb = new Bomb();
    Blockade *blockade = new Blockade();
    Airlift *airlift = new Airlift();
    Negotiate *negotiate = new Negotiate();

    list.add(deploy);
    list.add(advance);
    list.add(airlift);
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

    Deploy *deploy = new Deploy();
    Advance *advance = new Advance();
    Bomb *bomb = new Bomb();
    Blockade *blockade = new Blockade();
    Airlift *airlift = new Airlift();
    Negotiate *negotiate = new Negotiate();

    list.add(deploy);
    list.add(advance);
    list.add(airlift);
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
    Deploy *deploy = new Deploy();
    Advance *advance = new Advance();
    Bomb *bomb = new Bomb();
    Blockade *blockade = new Blockade();
    Airlift *airlift = new Airlift();
    Negotiate *negotiate = new Negotiate();

    list.add(deploy);
    list.add(advance);
    list.add(airlift);

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
