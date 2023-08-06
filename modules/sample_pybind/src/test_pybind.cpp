
#include <iostream>
#include <pybind11/pybind11.h>

int add(int a, int b) { return a + b; }

class Calculator {
  public:
    int add(int a, int b) { return a + b; }

    int subtract(int a, int b) { return a - b; }
};

namespace py = pybind11;

PYBIND11_MODULE(example_module, m) {
    m.def("add", &add, "A function that adds two numbers");
    py::class_<Calculator>(m, "Calculator")
        .def(py::init<>())
        .def("add", &Calculator::add, "A method that adds two numbers")
        .def("subtract", &Calculator::subtract,
             "A method that subtracts two numbers");
}
