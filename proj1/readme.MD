# Project 1

## Table of Contents
- [Project 1](#project-1)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
    - [Folders structure](#folders-structure)
  - [Installation](#installation)
    - [Requirements](#requirements)
    - [Installation](#installation-1)
    - [Compile](#compile)
  - [Usage](#usage)
    - [Test](#test)
        - [Computer specifications](#computer-specifications)
        - [Prime number checker](#prime-number-checker)
        - [Matrix multiplication](#matrix-multiplication)

## Introduction
This project was written in C++ because it's a language that I affectionate and I am familiar with. It includes an architecture made to be extensible and easy to maintain while reusing as much code as possible.

### Folders structure
```
├── xmake.lua
├── bin -> folder created after compilation
│   ├── MatmultD -> second problem executable
│   ├── pc_dynamic -> first problem executable (dynamic)
│   ├── pc_static_block -> first problem executable (static block)
│   ├── pc_static_cyclic -> first problem executable (static cyclic)
├── src
│   ├── xmake.lua
│   ├── problem1 -> contains the code for the first problem
│   │   ├── xmake.lua
│   │   ├── pc_serial.java.cpp -> translation of the basic java code to cpp
│   │   ├── dynamic
│   │   │   ├── xmake.lua
│   |   │   ├── Main.cpp
│   │   │   ├── DynamicThread.cpp and DynamicThread.hpp -> Child class of Thread
│   │   │   ├── WorkQueue.cpp and WorkQueue.hpp
│   │   ├── static_block
│   │   │   ├── xmake.lua
│   │   │   ├── Main.cpp
│   │   │   ├── StaticBlockThread.cpp and StaticBlockThread.hpp -> Child class of Thread
│   │   ├── static_cyclic
│   │   │   ├── xmake.lua
│   │   │   ├── Main.cpp
│   │   │   ├── StaticCyclicThread.cpp and StaticCyclicThread.hpp -> Child class of Thread
│   ├── problem2 -> contains the code for the second problem
│   │   ├── xmake.lua
│   │   ├── Main.cpp
│   │   ├── Matrix.cpp and Matrix.hpp
│   │   ├── MatrixThread.cpp and MatrixThread.hpp -> Child class of Thread
│   ├── Shared -> contains the code shared between the problems
│   │   ├── Clock.cpp and Clock.hpp
│   │   ├── PrimeChecker.cpp and PrimeChecker.hpp
│   │   ├── Thread.cpp and Thread.hpp
│   │   ├── ThreadPool.hpp -> No cpp file because it's a template class
├── data -> folder containing the test matrices
```

## Installation
### Requirements
- C++ compiler (g++, clang++, msvc++)
- XMake
- Git

### Installation
```bash
git clone git@github.com:GlassAlo/CAU_Multicore.git
cd CAU_Multicore/proj1
```

### Compile
```bash
xmake f -m release && xmake -y &&
```
- `-m release` is used to compile the project in release mode, which is faster than debug mode.
- `xmake -y` is used to compile the project. The `-y` flag is used to skip the confirmation prompt.
- `xmake` will create a `bin` folder with the executables inside.

## Usage
```bash
./bin/pc_dynamic <number of threads> <number end number>
./bin/pc_static_block <number of threads> <number end number>
./bin/pc_static_cyclic <number of threads> <number end number>
./bin/MatmultD <number of threads> < <path to matrix file>
```

- The first three executables are for the first problem, which is a prime number checker. The last one is for the second problem, which is a matrix multiplication.
- The first three executables take two arguments: the number of threads and the end number. The last one takes one argument: the number of threads and reads the matrix from a file.

### Test
#### Computer specifications
- OS: Garuda Linux Broadwing x86_64
- Kernel: 6.13.8-zen1-1-zen
- CPU: AMD Ryzen 9 5900HS with Radeon Graphics (16) @ 4.680GHz
    - Cores 8
        - Uniform core design
    - Threads 16
    - Base clock 3.0GHz
    - Max boost clock up to 4.6GHz
    - L3 cache 16MB
    - Memory PCIe 3.0
    - Supports Simultaneous Multithreading (SMT), with each cores supporting two threads
- Integrated GPU: AMD ATI Radeon Vega Series / Radeon Vega Mobile Series
- Discrete GPU: NVIDIA GeForce RTX 3080 Mobile / Max-Q (8GB/16GB)
- RAM: 32GB
- Disk: 1TB SSD
- Shell: zsh

#### Prime number checker
- All the tests were done with the same number of threads and the same end number.
- The end number was set to 1000000.
- The performance (1 / exec time) was multiplied by 10000 to have a better view of the evolution of the performance.

#### Performance Chart
![Prime Number Checker Performance](https://github.com/GlassAlo/CAU_Multicore/blob/main/proj1/doc/proj1.jpg)
