/*
** File: PrimeChecker.hpp                                                      *
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

#pragma once

#include <mutex>
#include <thread>

namespace Shared {
    class PrimeChecker
    {
        private:
            int _counter;
            std::mutex _counterMutex;
            PrimeChecker();

        public:
            static auto getInstance() -> PrimeChecker &;

            PrimeChecker(const PrimeChecker &) = delete;
            PrimeChecker(PrimeChecker &&) = delete;
            auto operator=(const PrimeChecker &) -> PrimeChecker & = delete;
            auto operator=(PrimeChecker &&) -> PrimeChecker & = delete;

            ~PrimeChecker() = default;

            auto incrementCounter(int &aToAdd) -> bool;
            [[nodiscard]] auto getCounter() const -> int;

            // Function to check if a number is prime
            static auto isPrime(int aNumber) -> bool;
    };
} // namespace Shared
