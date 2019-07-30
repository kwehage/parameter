#include <iostream>

#include "parameter.h"

int main() {

  Parameter::List context;

  std::string name;
  Parameter::KeyValue name_key_value(
    "name", &name, "descriptive name of Shift simulation context");
  context.add_parameter(name_key_value);

  Parameter::List model_parameters;
  Parameter::KeyValue model_parameters_key_value(
    "model_parameters", &model_parameters,
    "parameters to configure simulation");
  context.add_parameter(model_parameters_key_value);

  Parameter::List units;
  Parameter::KeyValue units_key_value("units", &units,
                                      "configure units for simulation");
  model_parameters.add_parameter(units_key_value);


  std::string length = "meters";
  Parameter::KeyValue length_key_value("length", &length, "units for length");
  units.add_parameter(length_key_value);

  std::cout
    << "length units: "
    << context["model_parameters"]["units"]["length"].value<std::string>()
    << std::endl;

  length = "feet";
  std::cout
    << "length units: "
    << context["model_parameters"]["units"]["length"].value<std::string>()
    << std::endl;

  return 0;
}
