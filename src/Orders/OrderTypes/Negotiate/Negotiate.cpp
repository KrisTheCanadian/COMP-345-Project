#include "Negotiate.h"

const std::string Negotiate::label = "Negotiate";

Negotiate::~Negotiate() = default;

std::string Negotiate::getLabel() const { return label; }

bool Negotiate::validate() const
{
  std::cout << "-> Negotiate order validation check" << std::endl;
  return true;
}

void Negotiate::execute() const
{
  if (validate()) { std::cout << "Negotiate execution." << std::endl; }
}


Order *Negotiate::clone() const { return new Negotiate(*this); }

std::ostream &Negotiate::orderCout(std::ostream &ostream) const {
  return ostream << "-> Negotiate order.";
}

