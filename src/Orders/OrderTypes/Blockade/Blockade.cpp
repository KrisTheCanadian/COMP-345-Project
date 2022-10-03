#include "Blockade.h"

const string Blockade::label = "Blockade";

Blockade::~Blockade() = default;

string Blockade::getLabel() const { return label; }

ostream &Blockade::orderCout(ostream &output) const { return output << "-> Blockade order."; }

bool Blockade::validate() const
{
  cout << "-> Blockade order validation check" << endl;
  return true;
}

void Blockade::execute() const
{
  if (validate()) { cout << "Blockade execution." << endl; }
}

Order *Blockade::clone() const { return new Blockade(*this); }