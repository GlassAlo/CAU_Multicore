/*
** File: PrimeChecker.cpp                                                      *
** Project: static_block                                                       *
** Created Date: We Apr 2025                                                   *
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

#include "PrimeChecker.hpp"

namespace Shared {
    PrimeChecker::PrimeChecker()
        : _counter(0)
    {}

    auto PrimeChecker::getInstance() -> PrimeChecker &
    {
        static PrimeChecker instance; // Guaranteed to be destroyed
        return instance;              // Instantiated on first use
    }

    auto PrimeChecker::incrementCounter(int &aToAdd) -> void
    {
        std::lock_guard<std::mutex> lock(_counterMutex);
        _counter += aToAdd;
        aToAdd = 0; // Reset the value to 0 after adding it to the counter
        _counterMutex.unlock();
    }

    [[nodiscard]] auto PrimeChecker::getCounter() const -> int
    {
        return _counter;
    }

    auto PrimeChecker::isPrime(int aNumber) -> bool
    {
        if (aNumber <= 1) {
            return false;
        }
        for (int i = 2; i < aNumber; i++) {
            if (aNumber % i == 0) {
                return false;
            }
        }
        return true;
    }
} // namespace Shared
