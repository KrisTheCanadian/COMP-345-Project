#include "Airlift.h"

const string Airlift::label = "Airlift";

Airlift::~Airlift() = default;

string Airlift::getLabel() const { return label; }

ostream &Airlift::orderCout(ostream &output) const { return output << "-> Airlift order."; }

bool Airlift::validate() const
{
  cout << "-> Airlift order validation check" << endl;
  return true;
}

void Airlift::execute() const
{
  if (validate()) { cout << "Airlift execution." << endl; }
}

Order *Airlift::clone() const { return new Airlift(*this); }