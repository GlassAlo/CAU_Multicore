/*
** File: Main.cpp                                                              *
** Project: prob2                                                              *
** Created Date: We May 2025                                                   *
** Author: GlassAlo                                                            *
** Email: ofourpatat@gmail.com                                                 *
** -----                                                                       *
** Description: {Enter a description for the file}                             *
** -----                                                                       *
** Last Modified: Wed May 14 2025                                              *
** Modified By: GlassAlo                                                       *
** -----                                                                       *
** Copyright (c) 2025 Aurea-Games                                              *
** -----                                                                       *
** HISTORY:                                                                    *
** Date      	By	Comments                                                   *
** ----------	---	---------------------------------------------------------  *
*/

#include <iostream>
#include <omp.h>
#include <syncstream>
#include <vector>

constexpr const int SEQUENTIAL_CUTOFF = 1000;
constexpr const int NUM_END_BASE = 10000;

namespace {
    long calculateParallelTotal(std::vector<long> &aArr, int aStart, int aEnd)
    {
        if ((aEnd - aStart) < SEQUENTIAL_CUTOFF) {
            long ans = 0;
            for (int i = aStart; i < aEnd; ++i) {
                ans += aArr[i];
            }
            return ans;
        } else {
            long left_sum = 0;
            long right_sum = 0;

#pragma omp task shared(left_sum) default(none) firstprivate(aArr, aStart, aEnd)
            left_sum = calculateParallelTotal(aArr, aStart, (aStart + aEnd) / 2);

#pragma omp task shared(right_sum) default(none) firstprivate(aArr, aStart, aEnd)
            right_sum = calculateParallelTotal(aArr, (aStart + aEnd) / 2, aEnd);

#pragma omp taskwait
            long total = left_sum + right_sum;
            std::osyncstream(std::cout) << "        sum(" << aStart << "to" << (aEnd - 1) << ")=" << total << '\n';
            return total;
        }
    }

    long calculateTotal(std::vector<long> &aArr, int aSize)
    {
        long result = 0;
#pragma omp parallel default(none) firstprivate(aArr, aSize) shared(result)
        {
#pragma omp single
            {
                result = calculateParallelTotal(aArr, 0, aSize);
            }
        }
        return result;
    }
} // namespace

int main(int argc, char *argv[])
{
    int NUM_END = NUM_END_BASE;
    if (argc == 2) {
        NUM_END = std::stoi(*(argv + 1));
    }

    std::vector<long> int_arr(NUM_END);
    for (int i = 0; i < NUM_END; ++i) {
        int_arr[i] = i + 1;
    }

    long total = calculateTotal(int_arr, NUM_END);
    std::cout << "sum from 1 to " << NUM_END << "=" << '\n';
    std::cout << total << '\n';

    return 0;
}
