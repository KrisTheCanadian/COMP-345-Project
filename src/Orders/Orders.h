#pragma once

#include <iostream>
#include "Cards/Cards.h"

class Card;
class Player;
class Territory;
enum CardType : int;

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Orders
//
// -----------------------------------------------------------------------------------------------------------------

// --------------------------------
// Abstract Order class data members and methods to be implemented by derived classes
// --------------------------------
class Order
{
public:
  // gets label
  virtual std::string getLabel() const = 0;
  // validates order
  virtual bool validate() const = 0;
  // executes order
  virtual void execute() const = 0;
  Order();
  explicit Order(Player &);
  // destructor
  virtual ~Order() = 0;
  // cloner (copy)
  virtual Order *clone() const = 0;

protected:
    Player *currentPlayer;
    bool enabled;

private:
  // --------------------------------
  // Operator Overloads
  // --------------------------------
  virtual std::ostream &orderCout(std::ostream &) const = 0;

  friend std::ostream &operator<<(std::ostream &, const Order &);
};



// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                OrdersList
//
// -----------------------------------------------------------------------------------------------------------------



class OrdersList
{
private:
  // vector of Order pointers
  std::vector<Order *> orders{};

public:
  // --------------------------------
  // Constructors + destructors
  // --------------------------------
  OrdersList() = default;
  ~OrdersList();
  OrdersList(const OrdersList &);

  // --------------------------------
  // Operator Overloads
  // --------------------------------
  OrdersList &operator=(const OrdersList &);

  // --------------------------------
  // Adders + mutators
  // --------------------------------
  void add(Order *o);
  void remove(int);
  void move(int, int);

  // Run user orders and remove them from order list
  void execute();

  int getOrdersListSize();
  Order* getOrder(int index);

  // --------------------------------
  // Getters
  // --------------------------------
  std::vector<Order *>* getList();

private:
  // --------------------------------
  // ostream overload
  // --------------------------------
  friend std::ostream &operator<<(std::ostream &, const OrdersList &);
};



// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Advance
//
// -----------------------------------------------------------------------------------------------------------------

    class Advance : public Order {
    public:
        Advance();

        Advance(Territory &, Territory &, Player &, int); // Src, dest, current player, amount
        ~Advance() override;

        std::string getLabel() const override;

        bool validate() const override;

        void execute() const override;

    private:
        const static std::string label;

        Order *clone() const override;

        std::ostream &orderCout(std::ostream &) const override;

        Territory *source;
        Territory *target;
        int *amount;
    };



// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Airlift
//
// -----------------------------------------------------------------------------------------------------------------



class Airlift : public Order
{
public:
  Airlift();
  Airlift(Territory &, Territory &, Player &, int); // Source, target, current player, amount
  ~Airlift() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;

  Territory *source;
  Territory *target;
  int *amount;
};



// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Blockade
//
// -----------------------------------------------------------------------------------------------------------------




class Blockade : public Order
{
public:
  Blockade();
  Blockade(Territory &, Player &); // Target, current player
  ~Blockade() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;

  Territory *target;
};


// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Bomb
//
// -----------------------------------------------------------------------------------------------------------------



class Bomb : public Order
{
public:
  Bomb();
  Bomb(Territory &, Player &); // Target territory to bomb, current player
  ~Bomb() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
  Territory *target;
};



// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Deploy
//
// -----------------------------------------------------------------------------------------------------------------



class Deploy : public Order
{
public:
    Deploy();
    Deploy(Territory &, Player &, int); // Target territory, current player, amount
    ~Deploy() override;
    std::string getLabel() const override;
    bool validate() const override;
    void execute() const override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
  Territory *target; // Target territory to deploy at
  int *amount; // Amount of armies to deploy
};




// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Negotiate
//
// -----------------------------------------------------------------------------------------------------------------


class Negotiate : public Order
{
public:
    Negotiate();
    Negotiate(Player &, Player &);
    ~Negotiate() override;
    std::string getLabel() const override;
    bool validate() const override;
    void execute() const override;  

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;

  Player *targetPlayer;
};

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                OrdersFactory
//
// -----------------------------------------------------------------------------------------------------------------

class OrdersFactory {

public:
    static Order* CreateOrder(CardType cardType);

};

void attackSimulation(Territory*, Territory*, Player*, int*);
