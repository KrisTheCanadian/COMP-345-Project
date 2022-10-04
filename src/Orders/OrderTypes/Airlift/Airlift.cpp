#include "Airlift.h"

const std::string Airlift::label = "Airlift";

Airlift::~Airlift() = default;

std::string Airlift::getLabel() const { return label; }

std::ostream &Airlift::orderCout(std::ostream &output) const { return output << "-> Airlift order."; }

bool Airlift::validate() const
{
  std::cout << "-> Airlift order validation check" << std::endl;
  return true;
}

void Airlift::execute() const
{
  if (validate()) { std::cout << "Airlift execution." << std::endl; }
}

Order *Airlift::clone() const { return new Airlift(*this); }