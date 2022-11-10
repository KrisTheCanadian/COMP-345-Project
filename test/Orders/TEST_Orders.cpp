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
    int temp;
    Deploy *deploy = new Deploy();

    {
        // --------------------------------
        // DUMMY VALUES FOR TESTING
        // --------------------------------
        int id1 = 10;
        int id2 = 20;

        int reinforcementPool1 = 20;
        int reinforcementPool2 = 20;

        cout << "-> Creating territories" << endl;
        Territory *t1 = new Territory("t1");
        t1->addArmyUnits(10);
        Territory *t2 = new Territory("t2");
        t2->addArmyUnits(10);
        Territory *t3 = new Territory("t3");
        t3->addArmyUnits(10);
        Territory *t4 = new Territory("t4");
        t4->addArmyUnits(10);
        Territory *t5 = new Territory("t5");
        t5->addArmyUnits(10);

        t1->addAdjacentTerritory(t2);
        t2->addAdjacentTerritory(t1);
        t2->addAdjacentTerritory(t3);
        t3->addAdjacentTerritory(t2);
        t3->addAdjacentTerritory(t4);
        t3->addAdjacentTerritory(t5);
        t4->addAdjacentTerritory(t3);
        t4->addAdjacentTerritory(t5);
        t5->addAdjacentTerritory(t3);
        t5->addAdjacentTerritory(t4);

        vector<Territory *> tList1 = {t1, t2, t4};
        vector<Territory *> tList2 = {t3, t5};

        Deck *deck = new Deck();

        deck->create_deck();

        Hand *hand1 = new Hand;
        Hand *hand2 = new Hand;

        for (int i = 0; i < 6; i++) {
            deck->draw(*hand1);
        }
        for (int i = 0; i < 6; i++) {
            deck->draw(*hand2);
        }

        Deploy *deploy = new Deploy();

        cout << "-> Creating list of orders" << endl;
        OrdersList *ordersList1 = new OrdersList();
        OrdersList *ordersList2 = new OrdersList();
        //OrdersFactory factory;

        ordersList1->add(deploy);
        ordersList2->add(deploy);

        cout << "-> Creating the players" << endl;
        Player *player1 = new Player(id1, reinforcementPool1, tList1, hand1, ordersList1);
        Player *player2 = new Player(id2, reinforcementPool2, tList2, hand2, ordersList2);

        cout << "-> Setting the players as territory owners" << endl;
        for (int i = 0; i < tList1.size(); i++) {
            tList1.at(i)->setOwnerId(player1->getId());
        }
        for (int i = 0; i < tList2.size(); i++) {
            tList2.at(i)->setOwnerId(player2->getId());
        }

        cout << "-> Adding the players to a list" << endl;
        Player *allPlayers = new Player();
        allPlayers->addPlayer(player1);
        allPlayers->addPlayer(player2);

        // --------------------------------
        // USER INPUTS
        // --------------------------------
        string sourceTerritory;
        string targetTerritory;
        int nbArmies;
        int negotiatePlayerID;

        // --------------------------------
        // DEPLOY EXECUTION WITH PLAYER 1
        // --------------------------------
    cout << "-> Deploy Execution with Player 1" << endl;
    cout << "Your territories are: " << endl;
    for (int i = 0; i < player1->getTerritories()->size(); i++) {
        cout << "\t" << player1->getTerritories()->at(i)->getName() << endl;
    }

        cout << "Which territory do you wish to deploy to?" << endl;
        targetTerritory = "t1";
        cout << "How many units from reinforcement pool do you wish to deploy?" << endl;
        nbArmies= 5;

        for (int i = 0; i < allPlayers->getListOfPlayers().size(); i++) {
            for (int j = 0; j < allPlayers->getListOfPlayers().at(i)->getTerritories()->size(); j++)
            {
                if (allPlayers->getListOfPlayers().at(i)->getTerritories()->at(j)->getName() == targetTerritory) {
                    deploy = new Deploy(*(allPlayers->getListOfPlayers().at(i)->getTerritories()->at(j)), *player1, nbArmies);
                }
            }
        }
    deploy->execute();
         temp = t1->getArmies();
    }
  // assert
  EXPECT_EQ(temp, 15);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
