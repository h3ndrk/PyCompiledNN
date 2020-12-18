#include <string>
#include <iostream>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include "CompiledNN.h"
#include "Model.h"

namespace py = boost::python;
namespace np = py::numpy;

np::ndarray greet()
{
  return np::zeros(py::make_tuple(3, 3), np::dtype::get_builtin<int>());
  // return "hello, world";
}

struct ModelWrapper
{
  NeuralNetwork::Model model;

  ModelWrapper() {}
  ModelWrapper(const std::string &file) : model{file} {}

  void setInputUInt8(std::size_t index)
  {
    model.setInputUInt8(index);
  }

  bool isInputUInt8(std::size_t index) const
  {
    return model.isInputUInt8(index);
  }

  void clear()
  {
    model.clear();
  }

  void load(const std::string &file)
  {
    model.load(file);
  }
};

BOOST_PYTHON_MODULE(PyCompiledNN)
{
  NeuralNetwork::Model model;
  Py_Initialize();
  np::initialize();
  py::def("greet", greet);
  py::class_<ModelWrapper, boost::noncopyable>("Model")
      .def(py::init<std::string>())
      .def("setInputUInt8", &ModelWrapper::setInputUInt8)
      .def("isInputUInt8", &ModelWrapper::isInputUInt8)
      .def("clear", &ModelWrapper::clear)
      .def("load", &ModelWrapper::load);
}
