#include "Blockade.h"

const std::string Blockade::label = "Blockade";

Blockade::~Blockade() = default;

std::string Blockade::getLabel() const { return label; }

std::ostream &Blockade::orderCout(std::ostream &output) const { return output << "-> Blockade order."; }

bool Blockade::validate() const
{
  std::cout << "-> Blockade order validation check" << std::endl;
  return true;
}

void Blockade::execute() const
{
  if (validate()) { std::cout << "Blockade execution." << std::endl; }
}

Order *Blockade::clone() const { return new Blockade(*this); }