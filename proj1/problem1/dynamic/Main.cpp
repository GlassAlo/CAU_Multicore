/*
** File: Main.cpp                                                              *
** Project: problem1                                                           *
** Created Date: We Apr 2025                                                   *
** Author: GlassAlo                                                            *
** Email: ofourpatat@gmail.com                                                 *
** -----                                                                       *
** Description: {Enter a description for the file}                             *
** -----                                                                       *
** Last Modified: Tue Apr 15 2025                                              *
** Modified By: GlassAlo                                                       *
** -----                                                                       *
** Copyright (c) 2025 Aurea-Games                                              *
** -----                                                                       *
** HISTORY:                                                                    *
** Date      	By	Comments                                                   *
** ----------	---	---------------------------------------------------------  *
*/

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <tuple>
#include <vector>
#include "Clock.hpp"
#include "DynamicThread.hpp"
#include "PrimeChecker.hpp"
#include "ThreadPool.hpp"
#include "WorkQueue.hpp"

constexpr int BASE_NUM_END = 200000;
constexpr int BASE_NUM_THREADS = 1;
constexpr int STEPS = 10;

int main(const int argc, const char **argv)
{
    int NUM_END = BASE_NUM_END;         // default input
    int NUM_THREADS = BASE_NUM_THREADS; // default number of threads
    Shared::Clock clock;
    Dynamic::WorkQueue workQueue;

    if (argc == 3) {
        NUM_THREADS = atoi(argv[1]);
        NUM_END = atoi(argv[2]);
    }
    int nbrOfRanges = NUM_END / STEPS;

    for (int i = 0; i < nbrOfRanges; i++) {
        int startNbr = i * STEPS;
        int endNbr = ((i + 1) * STEPS) - 1;
        std::tuple<int, int> range = std::make_tuple(startNbr, endNbr);

        workQueue.push(range);
    }

    Shared::ThreadPool<Dynamic::DynamicThread> threadPool(NUM_THREADS, workQueue);

    clock.start();

    threadPool.run();
    auto elapsedTimeInMs = clock.getElapsedTime();

    std::cout << "Program Execution Time: " << elapsedTimeInMs << " ms" << "\n";
    std::cout << "1..." << NUM_END - 1 << " prime number counter= " << Shared::PrimeChecker::getInstance().getCounter()
              << "\n";
    float performance = 1 / elapsedTimeInMs;
    std::cout << "Performance: 1/execution time = " << performance * 10000 << "\n";
}
