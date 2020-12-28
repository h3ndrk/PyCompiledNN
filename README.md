# PyCompiledNN

This repository contains Python bindings for [CompiledNN](https://github.com/bhuman/CompiledNN) (written by B-Human).

## Installation

This package requires the following dependencies:

- Python 3 (with NumPy) (Ubuntu/Debian: *python3*, *python3-numpy*)
- Boost Python (with NumPy) (Ubuntu/Debian: *libboost-python-dev*, *libboost-numpy-dev*)
- HDF5 (Ubuntu/Debian: *libhdf5-dev*)
- Protocol Buffers (both compiler and library) (Ubuntu/Debian: *libprotobuf-dev*)

*PyCompiledNN* can be installed via `pip install git+https://github.com/h3ndrk/PyCompiledNN.git`.

## Development

1. Make sure all submodules are cloned: `git submodule update --init`
2. Configure project: `cmake -Bbuild .`
3. Build project: `cmake --build build`
4. Observe the file `PyCompiledNN.so` in the `build` directory

For testing, you should be able to import the module in Python without errors:

1. Change into build directory: `cd build`
2. Run an interactive Python REPL: `python`
3. Import the module: `import PyCompiledNN`

## Example

The API is very similar to the [C++ version](https://github.com/bhuman/CompiledNN):

```py
import PyCompiledNN

model = PyCompiledNN.Model()
model.load('model.hdf5')
# Optionally, indicate which input tensors should be converted from unsigned chars to floats in the beginning.
# model.setInputUInt8(0);
nn = PyCompiledNN.CompiledNN()
nn.compile(model)
# ... fill nn.input(i) with data
nn.apply()
# ... obtain the results from nn.output(i)
```

The `input()` and `output()` methods return NumPy `ndarray`s:

```py
input_array = numpy.zeros((32, 32, 1))
numpy.copyto(nn.input(0), input_array, casting='no')
nn.apply()
print(nn.output(0))
```
