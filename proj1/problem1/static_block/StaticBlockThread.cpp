/*
** File: StaticBlockThread.cpp                                                 *
** Project: static_block                                                       *
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

#include "StaticBlockThread.hpp"
#include "PrimeChecker.hpp"

namespace StaticBlock {
    StaticBlockThread::StaticBlockThread(int idx, int startNbr, int endNbr)
        : Shared::Thread(idx),
          _startNbr(startNbr),
          _endNbr(endNbr)
    {}

    void StaticBlockThread::run()
    {
        _clock.start();

        Shared::PrimeChecker &primeChecker = Shared::PrimeChecker::getInstance();
        int counter = 0;

        for (int i = _startNbr; i <= _endNbr; i++) {
            if (primeChecker.isPrime(i)) {
                counter++;
            }
        }

        while (!primeChecker.incrementCounter(counter)) {
        }
        auto elapsedTimeInMs = _clock.getElapsedTime();
        std::cout << "Thread " << _idx << " Execution Time: " << elapsedTimeInMs << " ms"
                  << "\n";
    }

} // namespace StaticBlock
