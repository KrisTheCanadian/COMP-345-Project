#include "Bomb.h"

const string Bomb::label = "Bomb";

Bomb::~Bomb() = default;

string Bomb::getLabel() const { return label; }

ostream &Bomb::orderCout(ostream &output) const { return output << "-> Bomb order."; }

bool Bomb::validate() const
{
  cout << "-> Bomb order validation check" << endl;
  return true;
}

void Bomb::execute() const
{
  if (validate()) { cout << "Bomb execution." << endl; }
}

Order *Bomb::clone() const { return new Bomb(*this); }