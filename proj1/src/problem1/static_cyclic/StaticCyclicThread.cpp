/*
** File: StaticCyclicThread.cpp                                                *
** Project: static_cyclic                                                      *
** Created Date: Th Apr 2025                                                   *
** Author: GlassAlo                                                            *
** Email: ofourpatat@gmail.com                                                 *
** -----                                                                       *
** Description: {Enter a description for the file}                             *
** -----                                                                       *
** Last Modified: Wed Apr 09 2025                                              *
** Modified By: GlassAlo                                                       *
** -----                                                                       *
** Copyright (c) 2025 Aurea-Games                                              *
** -----                                                                       *
** HISTORY:                                                                    *
** Date      	By	Comments                                                   *
** ----------	---	---------------------------------------------------------  *
*/

#include "StaticCyclicThread.hpp"
#include <syncstream>
#include "PrimeChecker.hpp"

namespace StaticCyclic {
    StaticCyclicThread::StaticCyclicThread(int idx, std::vector<std::tuple<int, int>> &aArgs)
        : Shared::Thread(idx),
          _ranges(std::move(aArgs))
    {}

    void StaticCyclicThread::run()
    {
        _clock.start();

        Shared::PrimeChecker &primeChecker = Shared::PrimeChecker::getInstance();
        int counter = 0;

        for (const auto &[startNbr, endNbr] : _ranges) {
            for (int i = startNbr; i <= endNbr; i++) {
                if (primeChecker.isPrime(i)) {
                    counter++;
                }
            }
        }

        primeChecker.incrementCounter(counter);

        auto elapsedTimeInMs = _clock.getElapsedTime();

        std::osyncstream(std::cout) << "Thread " << _idx << " Execution Time: " << elapsedTimeInMs << " ms"
                                    << "\n";
    }
} // namespace StaticCyclic
