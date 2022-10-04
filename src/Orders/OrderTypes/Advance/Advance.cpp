#include "Advance.h"

std::ostream &Advance::orderCout(std::ostream &output) const { return output << "-> Advance order."; }

std::string Advance::getLabel() const { return label; }

Advance::~Advance() = default;

const std::string Advance::label = "Advance";

bool Advance::validate() const
{
  std::cout << "-> Advance order validation check" << std::endl;
  return true;
}

void Advance::execute() const
{
  if (validate()) { std::cout << "Advance execution." << std::endl; }
}

Order *Advance::clone() const { return new Advance(*this); }