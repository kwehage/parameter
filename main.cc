#include <iostream>

#include "parameter.h"

/*
   Parameter::List must be able to return using [] operator:
     * Parameter::KeyValue
     * Parameter::List
     * Parameter::Array

   Parameter::Array holds only Parameter::Lists of like type. must be able to
   return
    * Parameter::List

   Parameter::KeyValue must be able to return
     * Parameter::List
     * Parameter::Array
     * double
     * std::vector
     * float
     * int
     * bool
     * whatever.

    Parameter::KeyValue, Parameter::List and Parameter::Array all derive from
   Parameter::Base class.

   Parameter::Base["key"]

    Parameter::List contains a standard map of keys to Parameter::Base

    Parameter::Array contains a std::vector of Parameter::List types
    * A special requirement for Shift is that all entries in an array are the
    the same type and are only lists. Each entry must have the `name` keyword.
*/

int main() {

  /*
    root -> ParameterArray (array of Shift contexts)
      excavator -> ParameterList (a single Shift context)
        model_parameters -> ParameterList (parameters defining model)
          units -> ParameterList
            length -> ParameterKeyValue (string)
            time -> ParameterKeyValue
          gravity -> ParameterKeyValue
        fixed -> parameter list
        assemblies ->
  */

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

  // std::cout << "time units: "
  //           <<
  //           context["model_parameters"]["units"]["time"].value<std::string>()
  //           << std::endl;
  // std::cout
  //   << "angle units: "
  //   << context["model_parameters"]["units"]["angle"].value<std::string>()
  //   << std::endl;

  // ParameterArray assemblies;
  //
  // ParameterList assembly;
  // ParameterArray bodies;
  // ParameterArray joints;
  // ParameterArray force_modules;
  //
  // double test_double = 10.0;
  // std::string test_string = "testing";
  //
  // std::any any = &test_double;
  // double* test_double_ptr = std::any_cast<double*>(any);
  // std::cout << "test_double_ptr: " << *test_double_ptr << std::endl;
  //
  // std::cout << "Creating parameter list." << std::endl;
  //
  // ParameterList parameter_list = ParameterList();
  //
  // std::cout << "Adding test double." << std::endl;
  // parameter_list.add_parameter(
  //   Parameter("test_double", &test_double, "double test value"));
  //
  // std::cout << "Adding test string." << std::endl;
  // parameter_list.add_parameter(
  //   Parameter("test_string", &test_string, "string test value"));
  //
  // double* double_ptr = parameter_list["test_double"].data<double*>();
  // std::string* string_ptr =
  // parameter_list["test_string"].data<std::string*>();
  //
  // std::cout << "test_double: " << *double_ptr << std::endl;
  // std::cout << "test_string: " << *string_ptr << std::endl;
  //
  // std::cout << "test_double: " <<
  // parameter_list["test_double"].value<double>()
  //           << std::endl;
  // std::cout << "test_string: "
  //           << parameter_list["test_string"].value<std::string>() <<
  //           std::endl;
  //
  // std::cout << "test_double type: " <<
  // parameter_list["test_double"].type_name()
  //           << std::endl;
  //
  // std::cout << "valid keys:" << std::endl;
  // for(const auto& [key, value] : parameter_list.parameters()) {
  //   std::cout << key << std::endl;
  // }

  return 0;
}
