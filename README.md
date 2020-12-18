# PyCompiledNN

This repository contains Python bindings for [CompiledNN](https://github.com/bhuman/CompiledNN) (written by B-Human).

## Build

1. Make sure all submodules are cloned.
2. Create build directory: `mkdir build`
3. Change into build directory: `cd build`
4. Configure project: `cmake ..`
5. Build project: `cmake --build .`
6. Observe the file `PyCompiledNN.so` in the `build` directory

For testing, you should be able to import the module in Python without errors:

1. Run an interactive Python REPL: `python`
2. Import the module: `import PyCompiledNN`

## Usage

The API is very similar to the C++ version:

```py
import PyCompiledNN

model = PyCompiledNN.Model()
model.load('../positioner.hdf5')
# Optionally, indicate which input tensors should be converted from unsigned chars to floats in the beginning.
# model.setInputUInt8(0);
nn = PyCompiledNN.CompiledNN()
nn.compile(model)
# ... fill nn.input(i) with data
nn.apply()
# ... obtain the results from nn.output(i)
```

The `input()` and `output()` methods return NumPy `ndarray`s.
