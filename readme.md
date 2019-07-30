Parameter
---------

Test code to illustrate how to represent a hierarchy of parameters (i.e. such as loaded from a JSON file) in C++:
* Header only, easy to incorporate into other projects
* Does not yet support serialization to/from a file
* The `Parameter::KeyValue` class uses C++17 `std::any` to hold a pointer to diferent types of underlying data.
* Supports lists or arrays of lists of parameters
* A `Parameter::List` uses a `std::map` to support fast lookup by key.
* A `Parameter::Array` uses a `std::vector` to support lookup by index. Additionally, each list is required to have a "name" key-value pair and a unique name to support lookup by string (lookup by string uses an O(n) search).
* The hierarchy is traversed in the same way that dicts are accessed in Python
* A `Parameter::KeyValue` data structure does not own its data. It owns a pointer to its data, which allows the actual data to be managed or manipulated elsewhere in the code (for example the actual data could be a class member variable).

The following example illustrates how to access *Shift* parameter length units as a string (by reference):

```
std::string& length_units = context["model_parameters"]["units"]["length"].value<std::string>();
```

Or, get a raw pointer to the data as:

```
std::string* length_units_ptr = context["model_parameters"]["units"]["length"].data<std::string*>();
```

Refer to the `main.cc` file for more details. 
