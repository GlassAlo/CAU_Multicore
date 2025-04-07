/*
** File: DynamicThread.cpp                                                *
** Project: Dynamic                                                      *
** Created Date: Th Apr 2025                                                   *
** Author: GlassAlo                                                            *
** Email: ofourpatat@gmail.com                                                 *
** -----                                                                       *
** Description: {Enter a description for the file}                             *
** -----                                                                       *
** Last Modified: Thu Apr 03 2025                                              *
** Modified By: GlassAlo                                                       *
** -----                                                                       *
** Copyright (c) 2025 Aurea-Games                                              *
** -----                                                                       *
** HISTORY:                                                                    *
** Date      	By	Comments                                                   *
** ----------	---	---------------------------------------------------------  *
*/

#include "DynamicThread.hpp"
#include <syncstream>
#include "PrimeChecker.hpp"

namespace Dynamic {
    DynamicThread::DynamicThread(int idx, WorkQueue &workQueue)
        : Shared::Thread(idx),
          _workQueue(workQueue)
    {}

    void DynamicThread::run()
    {
        _clock.start();

        Shared::PrimeChecker &primeChecker = Shared::PrimeChecker::getInstance();
        int counter = 0;
        std::tuple<int, int> range;

        while (_workQueue.get().pop(range)) {
            int startNbr = std::get<0>(range);
            int endNbr = std::get<1>(range);

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
} // namespace Dynamic
