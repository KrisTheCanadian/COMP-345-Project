#include "Bomb.h"

const std::string Bomb::label = "Bomb";

Bomb::~Bomb() = default;

std::string Bomb::getLabel() const { return label; }

std::ostream &Bomb::orderCout(std::ostream &output) const { return output << "-> Bomb order."; }

bool Bomb::validate() const
{
  std::cout << "-> Bomb order validation check" << std::endl;
  return true;
}

void Bomb::execute() const
{
  if (validate()) { std::cout << "Bomb execution." << std::endl; }
}

Order *Bomb::clone() const { return new Bomb(*this); }