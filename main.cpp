#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

namespace py = boost::python;
namespace np = py::numpy;

np::ndarray greet()
{
  return np::zeros(py::make_tuple(3, 3), np::dtype::get_builtin<int>());
  // return "hello, world";
}

BOOST_PYTHON_MODULE(CompiledNN)
{
  Py_Initialize();
  np::initialize();
  py::def("greet", greet);
}
