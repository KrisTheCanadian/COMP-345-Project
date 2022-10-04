#include "Deploy.h"

const std::string Deploy::label = "Deploy";

Deploy::~Deploy() = default;

std::string Deploy::getLabel() const { return label; }

std::ostream &Deploy::orderCout(std::ostream &output) const { return output << "-> Deploy order."; }

bool Deploy::validate() const
{
  std::cout << "-> Deploy order validation check" << std::endl;
  return true;
}

void Deploy::execute() const
{
  if (validate()) { std::cout << "Deploy execution." << std::endl; }
}

Order *Deploy::clone() const { return new Deploy(*this); }