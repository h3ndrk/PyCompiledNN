#include <string>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include "CompiledNN.h"
#include "Model.h"

namespace py = boost::python;
namespace np = py::numpy;

struct ModelWrapper
{
  NeuralNetwork::Model model;

  ModelWrapper() = default;
  explicit ModelWrapper(const std::string &file) : model{file} {}

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

struct CompiledNNWrapper
{
  NeuralNetwork::CompiledNN compiledNN;
  py::object tensorOwner;

  void compile(const ModelWrapper &model)
  {
    compiledNN.compile(model.model);
  }

  bool valid() const
  {
    return compiledNN.valid();
  }

  std::size_t numOfInputs() const
  {
    return compiledNN.numOfInputs();
  }

  np::ndarray tensor2ndarray(NeuralNetwork::TensorXf &tensor)
  {
    const auto &shape{tensor.dims()};

    assert(shape.size() <= 4);

    switch (shape.size())
    {
    case 1:
      return np::from_data(tensor.data(), np::dtype::get_builtin<float>(), py::make_tuple(shape[0]), py::make_tuple(sizeof(float)), tensorOwner);
    case 2:
      return np::from_data(tensor.data(), np::dtype::get_builtin<float>(), py::make_tuple(shape[0], shape[1]), py::make_tuple(shape[1] * sizeof(float), sizeof(float)), tensorOwner);
    case 3:
      return np::from_data(tensor.data(), np::dtype::get_builtin<float>(), py::make_tuple(shape[0], shape[1], shape[2]), py::make_tuple(shape[1] * shape[2] * sizeof(float), shape[2] * sizeof(float), sizeof(float)), tensorOwner);
    case 4:
      return np::from_data(tensor.data(), np::dtype::get_builtin<float>(), py::make_tuple(shape[0], shape[1], shape[2], shape[3]), py::make_tuple(shape[1] * shape[2] * shape[3] * sizeof(float), shape[2] * shape[3] * sizeof(float), shape[3] * sizeof(float), sizeof(float)), tensorOwner);
    case 0:
    default:
      return np::empty(py::make_tuple(), np::dtype::get_builtin<float>());
    }
  }

  np::ndarray input(std::size_t index)
  {
    return tensor2ndarray(compiledNN.input(index));
  }

  std::size_t numOfOutputs() const
  {
    return compiledNN.numOfOutputs();
  }

  np::ndarray output(std::size_t index)
  {
    return tensor2ndarray(compiledNN.output(index));
  }

  void apply() const
  {
    compiledNN.apply();
  }
};

BOOST_PYTHON_MODULE(PyCompiledNN)
{
  Py_Initialize();
  np::initialize();

  py::class_<ModelWrapper, boost::noncopyable>("Model")
      .def(py::init<std::string>())
      .def("setInputUInt8", &ModelWrapper::setInputUInt8)
      .def("isInputUInt8", &ModelWrapper::isInputUInt8)
      .def("clear", &ModelWrapper::clear)
      .def("load", &ModelWrapper::load);

  py::class_<CompiledNNWrapper, boost::noncopyable>("CompiledNN")
      .def("compile", &CompiledNNWrapper::compile)
      .def("valid", &CompiledNNWrapper::valid)
      .def("numOfInputs", &CompiledNNWrapper::numOfInputs)
      .def("input", &CompiledNNWrapper::input)
      .def("numOfOutputs", &CompiledNNWrapper::numOfOutputs)
      .def("output", &CompiledNNWrapper::output)
      .def("apply", &CompiledNNWrapper::apply);
}
