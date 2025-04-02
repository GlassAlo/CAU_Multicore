/*
** File: Main.cpp                                                              *
** Project: problem1                                                           *
** Created Date: We Apr 2025                                                   *
** Author: GlassAlo                                                            *
** Email: ofourpatat@gmail.com                                                 *
** -----                                                                       *
** Description: {Enter a description for the file}                             *
** -----                                                                       *
** Last Modified: Wed Apr 02 2025                                              *
** Modified By: GlassAlo                                                       *
** -----                                                                       *
** Copyright (c) 2025 Aurea-Games                                              *
** -----                                                                       *
** HISTORY:                                                                    *
** Date      	By	Comments                                                   *
** ----------	---	---------------------------------------------------------  *
*/

#include <cstdlib>
#include <iostream>
#include "Clock.hpp"
#include "PrimeChecker.hpp"
#include "StaticBlockThread.hpp"
#include "ThreadPool.hpp"

constexpr int BASE_NUM_END = 200000;

int main(const int argc, const char **argv)
{
    int NUM_END = BASE_NUM_END; // default input
    int NUM_THREADS = 1;        // default number of threads
    Shared::Clock clock;

    if (argc == 3) {
        NUM_END = atoi(argv[1]);
        NUM_THREADS = atoi(argv[2]);
    }

    Shared::ThreadPool<StaticBlock::StaticBlockThread> threadPool(NUM_THREADS, NUM_END);

    clock.start();

    threadPool.run();
    auto elapsedTimeInMs = clock.getElapsedTime();

    std::cout << "Program Execution Time: " << elapsedTimeInMs << " ms" << "\n";
    std::cout << "1..." << NUM_END - 1 << " prime number counter= " << Shared::PrimeChecker::getInstance().getCounter()
              << "\n";
    std::cout << "Performance: 1/execution time = " << 1 / elapsedTimeInMs << "\n";
}
