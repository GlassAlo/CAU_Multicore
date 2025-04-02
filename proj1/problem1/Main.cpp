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

#include <chrono>
#include <cstdlib>
#include <iostream>

namespace {
    constexpr int BASE_NUM_END = 200000;

    auto isPrime(int aNumber) -> bool
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
} // namespace

int main(const int argc, const char **argv)
{
    int NUM_END = BASE_NUM_END; // default input
    int NUM_THREADS = 1;        // default number of threads
    int counter = 0;

    if (argc == 3) {
        NUM_END = atoi(argv[1]);
        NUM_THREADS = atoi(argv[2]);
    }

    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_END; i++) {
        if (isPrime(i)) {
            counter++;
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsedTime = endTime - startTime;

    std::cout << "Program Execution Time: " << elapsedTime.count() << " ms" << "\n";
    std::cout << "1..." << NUM_END - 1 << " prime number counter= " << counter << "\n";
}
