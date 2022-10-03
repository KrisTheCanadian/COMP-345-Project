#include "Advance.h"

ostream &Advance::orderCout(ostream &output) const { return output << "-> Advance order."; }

string Advance::getLabel() const { return label; }

Advance::~Advance() = default;

const string Advance::label = "Advance";

bool Advance::validate() const
{
  cout << "-> Advance order validation check" << endl;
  return true;
}

void Advance::execute() const
{
  if (validate()) { cout << "Advance execution." << endl; }
}

Order *Advance::clone() const { return new Advance(*this); }