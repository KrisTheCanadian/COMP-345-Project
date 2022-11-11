#include "Orders.h"
#include "OrdersDriver.h"
#include "GameEngine/GameEngine.h"
using namespace std;

void testOrderExecution()
{
    // --------------------------------
    // DUMMY VALUES FOR TESTING
    // --------------------------------
    int id1 = 10;
    int id2 = 20;

    int reinforcementPool1 = 20;
    int reinforcementPool2 = 20;

    cout << "-> Creating territories" << endl;
    auto t1 = new Territory("t1");
    t1->addArmyUnits(10);
    auto t2 = new Territory("t2");
    t2->addArmyUnits(10);
    auto t3 = new Territory("t3");
    t3->addArmyUnits(10);
    auto t4 = new Territory("t4");
    t4->addArmyUnits(10);
    auto t5 = new Territory("t5");
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

    vector<Territory*> tList1 = { t1,t2, t4 };
    vector<Territory*> tList2 = { t3, t5 };


    Deck* deck = new Deck();
    deck->create_deck();

    Hand* hand1 = new Hand;
    Hand* hand2 = new Hand;

    for (int i = 0; i < 6; i++) {
        deck->draw(*hand1);
    }
    for (int i = 0; i < 6; i++) {
        deck->draw(*hand2);
    }

    auto deploy = new Deploy();
    auto advance = new Advance();
    auto bomb = new Bomb();
    auto blockade = new Blockade();
    auto airlift = new Airlift();
    auto negotiate = new Negotiate();

    cout << "-> Creating list of orders" << endl;
    auto ordersList1 = new OrdersList();
    auto ordersList2 = new OrdersList();

    ordersList1->add(deploy);
    ordersList1->add(advance);
    ordersList1->add(bomb);
    ordersList1->add(blockade);
    ordersList1->add(airlift);
    ordersList1->add(negotiate);

    ordersList2->add(deploy);
    ordersList2->add(advance);
    ordersList2->add(bomb);
    ordersList2->add(blockade);
    ordersList2->add(airlift);
    ordersList2->add(negotiate);

    cout << "-> Creating the players" << endl;
    auto player1 = new Player(id1, reinforcementPool1, tList1, hand1, ordersList1);
    auto player2 = new Player(id2, reinforcementPool2, tList2, hand2, ordersList2);

    cout << "-> Setting the players as territory owners" << endl;
    for (auto & i : tList1) {
        i->setOwnerId(player1->getId());
    }
    for (auto & i : tList2) {
        i->setOwnerId(player2->getId());
    }

    cout << "-> Adding the players to a list" << endl;
    auto allPlayers = new Player();
    allPlayers->addPlayer(player1);
    allPlayers->addPlayer(player2);

    // --------------------------------
    // USER INPUTS
    // --------------------------------
    string sourceTerritory;
    string targetTerritory;
    int nbArmies;
    int negotiatePlayerID;
    int userChoice;

    cout << "Which order execution would you like to test?" << endl;
    cout << "-> Enter 1 for Deploy Testing" << endl;
    cout << "-> Enter 2 for Advance Testing" << endl;
    cout << "-> Enter 3 for Bomb Testing" << endl;
    cout << "-> Enter 4 for Blockade Testing" << endl;
    cout << "-> Enter 5 for Airlift Testing" << endl;
    cout << "-> Enter 6 for Negotiate Testing" << endl;

    cout << "Please enter your choice: " << endl;
    cin >> userChoice;


    // --------------------------------
    // DEPLOY EXECUTION WITH PLAYER 1
    // --------------------------------
    if(userChoice == 1) {
        cout << "-> Deploy Execution with Player 1" << endl;
        cout << "Your territories are: " << endl;
        for (auto & i : *player1->getTerritories()) {
            cout << "\t" << i->getName() << endl;
        }

        cout << "Which territory do you wish to deploy to?" << endl;
        cin >> targetTerritory;
        cout << "How many units from reinforcement pool do you wish to deploy?" << endl;
        cin >> nbArmies;

        for (int i = 0; i < allPlayers->getListOfPlayers().size(); i++) {
            for (int j = 0; j < allPlayers->getListOfPlayers().at(i)->getTerritories()->size(); j++)
            {
                if (allPlayers->getListOfPlayers().at(i)->getTerritories()->at(j)->getName() == targetTerritory) {
                    deploy = new Deploy(*(allPlayers->getListOfPlayers().at(i)->getTerritories()->at(j)), *player1, nbArmies);
                }
            }
        }
        deploy->execute();
    }


    // --------------------------------
    // ADVANCE EXECUTION WITH PLAYER 2
    // --------------------------------
    if(userChoice == 2) {
        cout << "-> ADVANCE Execution with Player 2" << endl;
        cout << "Your territories are " << endl;
        for (auto & i : *player2->getTerritories()) {
            cout << "\t" << i->getName() << endl;
        }

        cout << "Your enemy with" << endl;
        for (int i = 0; i < allPlayers->getListOfPlayers().size(); i++) {
            if (allPlayers->getListOfPlayers().at(i) != player2) {
                cout << "\t PLayer ID: " << allPlayers->getListOfPlayers().at(i)->getId() << "'s territories are: " << endl;
                for (int j = 0; j < allPlayers->getListOfPlayers().at(i)->getTerritories()->size(); j++) {
                    cout << "\t\t" << allPlayers->getListOfPlayers().at(i)->getTerritories()->at(j)->getName() << endl;
                }
            }
        }


        cout << "From which territory do you wish to advance your army?" << endl;
        cin >> sourceTerritory;
        cout << "To which territory do you wish to advance your army?" << endl;
        cin >> targetTerritory;


        for (int i = 0; i < allPlayers->getListOfPlayers().size(); i++) {
            for (int j = 0; j < allPlayers->getListOfPlayers().at(i)->getTerritories()->size(); j++) {
                // Search for territory having the name of the source territory
                if (allPlayers->getListOfPlayers().at(i)->getTerritories()->at(j)->getName() == sourceTerritory) {

                    for (int k = 0; k < allPlayers->getListOfPlayers().size(); k++) {
                        for (int l = 0; l < allPlayers->getListOfPlayers().at(k)->getTerritories()->size(); l++) {
                            // Search for territory having the name of the target territory
                            if (allPlayers->getListOfPlayers().at(k)->getTerritories()->at(l)->getName() == targetTerritory) {
                                cout << "How many units do you wish to move? You have " << allPlayers->getListOfPlayers().at(i)->getTerritories()->at(j)->getArmies()
                                     << " units in " << allPlayers->getListOfPlayers().at(i)->getTerritories()->at(j)->getName() << endl;
                                cin >> nbArmies;

                                advance = new Advance(*(allPlayers->getListOfPlayers().at(i)->getTerritories()->at(j)), *(allPlayers->getListOfPlayers().at(k)->getTerritories()->at(l)), *player2, nbArmies);
                            }
                        }
                    }
                }
            }
        }

        advance->execute();
    }


    // --------------------------------
    // BOMB EXECUTION WITH PLAYER 1
    // --------------------------------
    if(userChoice == 3) {
        cout << "-> Bomb execution with player 1" << endl;
        cout << "Your enemy with " << endl;
        for (int i = 0; i < allPlayers->getListOfPlayers().size(); i++) {
            if (allPlayers->getListOfPlayers().at(i) != player1) {
                cout << "\t Player ID: " << allPlayers->getListOfPlayers().at(i)->getId() << "'s territories are " << endl;
                for (int j = 0; j < allPlayers->getListOfPlayers().at(i)->getTerritories()->size(); j++) {
                    cout << "\t\t" << allPlayers->getListOfPlayers().at(i)->getTerritories()->at(j)->getName() << endl;
                }
            }
        }

        cout << "Which territory do you wish to bomb? " << endl;
        cin >> targetTerritory;

        for (int i = 0; i < allPlayers->getListOfPlayers().size(); i++) {
            for (int j = 0; j < allPlayers->getListOfPlayers().at(i)->getTerritories()->size(); j++) {
                if (allPlayers->getListOfPlayers().at(i)->getTerritories()->at(j)->getName() == targetTerritory) {
                    bomb = new Bomb(*(allPlayers->getListOfPlayers().at(i)->getTerritories()->at(j)), *player1);
                }
            }
        }

        bomb->execute();
    }


    // --------------------------------
    // BLOCKADE EXECUTION WITH PLAYER 2
    // --------------------------------
    if(userChoice == 4) {
        cout << "-> Blockade execution with player 2" << endl;
        cout << "Your territories are: " << endl;
        for (auto & i : *player2->getTerritories()) {
            cout << "\t" << i->getName() << endl;
        }

        cout << "Which territory do you wish to block?" << endl;
        cin >> targetTerritory;

        for (int i = 0; i < allPlayers->getListOfPlayers().size(); i++) {
            for (int j = 0; j < allPlayers->getListOfPlayers().at(i)->getTerritories()->size(); j++) {
                if (allPlayers->getListOfPlayers().at(i)->getTerritories()->at(j)->getName() == targetTerritory) {
                    blockade = new Blockade(*(allPlayers->getListOfPlayers().at(i)->getTerritories()->at(j)), *player2);
                }
            }

        }
        blockade->execute();
    }


    // --------------------------------
    // AIRLIFT EXECUTION WITH PLAYER 1
    // --------------------------------
    if(userChoice == 5) {
        cout << "-> Airlift execution with player 1" << endl;
        cout << "Your territories are: " << endl;
        for (auto & i : *player1->getTerritories())
        {
            cout << "\t" << i->getName() << endl;
        }
        cout << "Your opponents territories are: " << endl;
        for (auto & i : *player2->getTerritories())
        {
            cout << "\t" << i->getName() << endl;
        }
        cout << "From which territory do you wish to airlift?" << endl;
        cin >> sourceTerritory;
        cout << "To which territory do you wish to airlift?" << endl;
        cin >> targetTerritory;
        for (int i = 0; i < allPlayers->getListOfPlayers().size(); i++)
        {
            for (int j = 0; j < allPlayers->getListOfPlayers().at(i)->getTerritories()->size(); j++)
            {
                // Search for territory having the name of the source territory
                if (allPlayers->getListOfPlayers().at(i)->getTerritories() -> at(j)->getName() == sourceTerritory)
                {
                    for (int k = 0; k < allPlayers->getListOfPlayers().size(); k++)
                    {
                        for (int l = 0; l < allPlayers->getListOfPlayers().at(k)->getTerritories()->size(); l++)
                        {
                            // Search for territory having the name of the target territory
                            if (allPlayers->getListOfPlayers().at(k)->getTerritories()->at(l)->getName() == targetTerritory)
                            {
                                cout << "How many units do you wish to move? You have " << allPlayers->getListOfPlayers().at(i)->getTerritories()->at(j)->getArmies()
                                     << " units in " << allPlayers->getListOfPlayers().at(i)->getTerritories()->at(j)->getName() << endl;
                                cin >> nbArmies;

                                airlift = new Airlift(*(allPlayers->getListOfPlayers().at(i)->getTerritories()->at(j)), *(allPlayers->getListOfPlayers().at(k)->getTerritories()->at(l)), *player1, nbArmies );
                            }
                        }
                    }
                }
            }
        }
        airlift->execute();
    }


    // --------------------------------
    // NEGOTIATE EXECUTION WITH PLAYER 1
    // --------------------------------
    if(userChoice == 6) {

        cout << "-> Negotiate execution with player 2" << endl;
        cout << "List of players:" << endl;
        for (int i = 0; i < allPlayers->getListOfPlayers().size(); i++)
        {
            cout << "\t PLayer ID: " << allPlayers->getListOfPlayers().at(i)->getId() << endl;
        }
        cout << "Which player do you wish to negotiate with? (Cin the player ID) " << endl;
        cin >> negotiatePlayerID;

        for (int i = 0; i < allPlayers->getListOfPlayers().size(); i++)
        {
            if (allPlayers->getListOfPlayers().at(i)->getId() == negotiatePlayerID)
            {
                negotiate = new Negotiate(*(allPlayers->getListOfPlayers().at(i)), *player2);
            }
        }

        negotiate->execute();
    }



//    deploy->~Deploy();
//    advance->~Advance();
//    bomb->~Bomb();
//    blockade->~Blockade();
//    airlift->~Airlift();

}
