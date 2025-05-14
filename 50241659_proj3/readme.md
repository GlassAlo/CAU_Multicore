# Project 3

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

## Introduction
This project was written in C++ and uses OpenMP 


### Folders structure
```
├── xmake.lua
├── bin -> folder created after compilation
│   ├── prob1 -> first problem executable
│   ├── prob2-> second problem executable
├── problem1 -> contains the code for the first problem
│   ├── xmake.lua
│   ├── prob1.cpp -> problem 1 source code
├── problem2 -> contains the code for the second problem
│   ├── xmake.lua
│   ├── prob2.cpp -> problem 2 source code
```

## Installation
### Requirements
- C++ compiler (g++, clang++, msvc++)
- XMake
- Git
- OpenMP

### Installation
```bash
git clone git@github.com:GlassAlo/CAU_Multicore.git
cd CAU_Multicore/proj3
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
./bin/prob1 <scheduling type> <number of threads>
./bin/prob2 <number end>
```