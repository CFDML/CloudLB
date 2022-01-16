# CloudLB: Portable Lattice Boltzmann Simulator

[![CI](https://img.shields.io/github/workflow/status/vavrines/CloudLB/CI?style=flat-square)](https://github.com/vavrines/CloudLB/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat-square)](https://opensource.org/licenses/MIT)

The CloudLB framework is a high-performance open source platform for solving the lattice Boltzmann equation, which is commonly adopted to fluid dynamics.

## Build
### Required dependencies
- Compiler with C++17 support
- cmake >= v3.16
- BLAS
- LAPACK
- OpenMP
- git

### Obtain submodules
Note that an **active internet connection is required for the first build** in order to download the suitable versions of the required submodules!
For the first build only, download all submodules:

```bash
git submodule update --init --recursive
```

### Compile the code
The executable file can be build with cmake workflow:
 
```bash 
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
make -j N
```

## Run
Execute the compiled binary by handing over a [valid config file](https://kit-rt.readthedocs.io/en/latest/configFiles.html), e.g.:

```bash
./cloud ../input/config.ini
```

### Format the code
The code can be formatted with the [clang-format](https://clang.llvm.org/docs/ClangFormat.html) tool:

```
clang-format -style=file -i src/xxx.cpp
```
