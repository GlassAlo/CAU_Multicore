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
        - [🖥️ Hardware Specifications](#hardware-specifications)
        - [Prime number checker](#prime-number-checker)
            - [🧪 Experiment Setup](#experiment-setup)
            - [📊 Performance Chart](#performance-chart)
            - [🧠 Interpretation](#interpretation)
            - [🏁 Conclusion](#conclusion)
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
#### 🖥️ Hardware Specifications
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

- Using Arch Linux with the Zen kernel for better performance comes with a cost, the pilots might not be very efficient and stable.

#### Prime number checker
##### 🧪 Experiment Setup
We measured the execution time and derived performance index using:
    - Static load balancing (block-wise)
    - Static load balancing (cyclic with task size 10)
    - Dynamic load balancing (task size 10)

Each implementation was tested using 1, 2, 4, 6, 8, 10, 12, 14, 16, and 32 threads, with execution times measured in milliseconds (ms).
The performance index was defined as:
- Performance Index = (1/Execution Time) × 10,000
This means that higher values indicate better performance.

- All the tests were done with the same number of threads and the same end number.
- The end number was set to 1000000.
- The performance (1 / exec time) was multiplied by 10000 to have a better view of the evolution of the performance.

##### 📊 Performance Chart
![Prime Number Checker Performance](https://raw.githubusercontent.com/GlassAlo/CAU_Multicore/169807d7aeb8380ee6524d94c4c9f7ddbfa57efb/proj1/doc/proj1.png)

##### 🧠 Interpretation
- `Static block` shows the worst scalability: the fixed partitioning results in some threads finishing early, causing CPU underutilization.
- `Static cyclic (task size = 10)` improves balance by distributing work in round-robin fashion. This reduces idle time and improves throughput.
- `Dynamic scheduling (task-stealing style)` performs the best or ties with static cyclic at almost all thread counts. It efficiently distributes remaining work to idle threads, particularly useful when some rows are more computationally expensive.
- Beyond 16 threads, there's almost no performance gain — this suggests we're reaching the limits of physical cores and memory/cache throughput.

##### 🏁 Conclusion
- The best performance is achieved with dynamic scheduling using 8 to 16 threads.
- Static cyclic offers nearly the same benefits with slightly more predictable performance curves.
- Static block is easy to implement but inefficient for larger thread counts due to uneven workload distribution.
- The speedup stabilizes after 16 threads due to hardware constraints, indicating that further performance gains would require either different algorithms, GPU acceleration, or architecture-specific optimizations.

#### Matrix multiplication
##### 🧪 Experiment Setup
We measured the execution time and derived performance index using:
    - Static load balancing (block-wise) because a matrix is a 2D array without any indication of the difficulty of the rows.

Each implementation was tested using 1, 2, 4, 6, 8, 10, 12, 14, 16, and 32 threads, with execution times measured in milliseconds (ms).
The performance index was defined as:
- Performance Index = (1/Execution Time)
This means that higher values indicate better performance.

- All the tests were done with the same number of threads and the same end number.
- The task size was evenly distributed between the threads (static block : rows / threads).
- The performance (1 / exec time) to have a better view of the evolution of the performance.
- The matrix size was set to 1000x1000.

##### 📊 Performance Chart
![Matrix Multiplication Performance](https://raw.githubusercontent.com/GlassAlo/CAU_Multicore/main/doc/proj2.png)

##### 🧠 Interpretation of Results
- Static block decomposition divides the matrix into contiguous row blocks per thread. This is easy to implement and efficient when all rows take similar time to process.
- The performance improves significantly as threads increase from 1 to 8, leveraging parallelism on available physical and logical cores.
- From 10 to 16 threads, performance still increases slightly due to Hyper-Threading.
- At 32 threads, performance degrades because the number of threads exceeds the number of logical cores, leading to context switching and scheduling overhead.
- The best performance (lowest execution time and highest index) is observed at 16 threads, suggesting that this is near-optimal for the hardware used.

##### 🏁 Conclusio
Using static block decomposition, the matrix multiplication program achieves good parallel scalability up to the hardware limit. The optimal performance is reached at 16 threads, with diminishing returns and overhead beyond that point. Static block partitioning is a good choice when matrix rows are uniform in complexity.

However, this method assumes perfect load balance, which is not guaranteed if some rows are more computationally expensive than others or if threads finish at different times. In such cases, dynamic work balancing (where idle threads can steal or request new tasks) would significantly improve efficiency, particularly at higher thread counts. This would reduce idle time and improve cache locality, potentially pushing performance beyond what static methods can achieve.
