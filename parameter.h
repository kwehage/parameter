#include <any>
#include <assert.h>
#include <cxxabi.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct BadAccessException : public std::exception {
  const char* what() const throw() {
    return "Parameter::KeyValue cannot be accessed using [] operator";
  }
};

struct ParameterNotFoundException : public std::exception {
  const char* what() const throw() {
    return "The requested key was not found";
  }
};

namespace Parameter {

class KeyValue;
class List;
class Array;


class KeyValue {
public:
  KeyValue() {}

  KeyValue(const std::string key, double* data, const std::string description)
    : key_(key)
    , data_(data)
    , description_(description) {}

  KeyValue(const std::string key, std::string* data,
           const std::string description)
    : key_(key)
    , data_(data)
    , description_(description) {}

  KeyValue(const std::string key, List* data, const std::string description)
    : key_(key)
    , data_(data)
    , description_(description)
    , is_list_(true) {}

  KeyValue(const std::string key, Array* data, const std::string description)
    : key_(key)
    , data_(data)
    , description_(description)
    , is_array_(true) {}

  ~KeyValue() {}

  const std::string& key() {
    return key_;
  }

  const std::string& description() {
    return description_;
  }

  template <typename T> const T data() {
    return std::any_cast<T>(data_);
  }

  template <typename T> const T& value() {  
    return *std::any_cast<T*>(data_);
  }

  KeyValue& operator[](const std::string);

  KeyValue& operator[](const char* key_str);

  const std::type_info& type_info() {
    return data_.type();
  }

  const std::string type_name() {
    int status;
    std::string type_str = data_.type().name();
    char* demangled_name =
      abi::__cxa_demangle(type_str.c_str(), NULL, NULL, &status);
    if(status == 0) {
      type_str = demangled_name;
      std::free(demangled_name);
      if(type_str.substr(type_str.length() - 1, type_str.length()) ==
         std::string("*")) {
        type_str = type_str.substr(0, type_str.length() - 1);
      }
    }
    return type_str;
  }

protected:
  std::string key_;
  std::any data_;
  std::string description_;

  bool is_array_ = false;
  bool is_list_ = false;
};

class List {

public:
  List() {}
  ~List() {}

  auto& parameters() const {
    return parameter_map_;
  }

  void add_parameter(KeyValue parameter) {
    const std::string key = parameter.key();
    parameter_map_[key] = parameter;
  }

  KeyValue& operator[](const char* key) {
    return parameter_map_[key];
  }

  KeyValue& operator[](std::string key) {
    return parameter_map_[key];
  }

  bool has_key(const std::string key) const {
    return parameter_map_.count(key);
  }

private:
  std::map<std::string, KeyValue> parameter_map_;
};

class Array {
public:
  Array() {}
  ~Array() {}

  KeyValue& operator[](const std::string key_str) {
    for(auto& parameter : parameter_array_) {
      if(parameter["name"].value<std::string>() == key_str) {
        return parameter;
      }
    }
    throw ParameterNotFoundException();
    return void_;
  }

  KeyValue& operator[](const char* key_str) {
    return operator[](std::string(key_str));
  }

  KeyValue& operator[](unsigned int index) {
    return parameter_array_[index];
  }

  size_t size() {
    return parameter_array_.size();
  }

  void add_parameter_list(List parameter) {
    if(!parameter.has_key("name")) {
      assert(0);
    }
    for(auto& parameter_test : parameter_array_) {
      if(parameter["name"].value<std::string>() ==
         parameter_test["name"].value<std::string>()) {
        assert(0);
      }
    }
  }

private:
  std::vector<KeyValue> parameter_array_;
  KeyValue void_;
};

KeyValue& KeyValue::operator[](const std::string key_str) {
  if(is_list_) {
    return (*(std::any_cast<Parameter::List*>(data_)))[key_str];
  } else if(is_array_) {
    return (*(std::any_cast<Parameter::Array*>(data_)))[key_str];
  } else {
    throw BadAccessException();
    return (std::any_cast<List>(data_))[key_str];
  }
}

KeyValue& KeyValue::operator[](const char* key_str) {
  return operator[](std::string(key_str));
}

} // namespace Parameter
