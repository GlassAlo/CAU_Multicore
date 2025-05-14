/*
** File: Main.cpp                                                              *
** Project: prob1                                                              *
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

#include <cmath>
#include <iostream>
#include <omp.h>
#include <string>

constexpr const int MAX_NUM = 200000;
constexpr const int CHUNK_SIZE = 10;

namespace {
    int is_prime(int nbr)
    {
        if (nbr <= 1) {
            return 0;
        }
        int root = (int) sqrt(nbr);
        for (int i = 2; i <= root; ++i) {
            if (nbr % i == 0) {
                return 0;
            }
        }
        return 1;
    }
} // namespace

int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cout << "Usage: " << *argv << " <scheduling_type (1-4)> <num_threads>\n";
        std::cout << "1: static, 2: dynamic, 3: static with chunk size, 4: dynamic with chunk size\n" << "\n";
        return 1;
    }

    auto scheduleType = std::stoi(*(argv + 1));
    auto numThreads = std::stoi(*(argv + 2));

    omp_set_num_threads(numThreads);

    omp_sched_t schedule_kind = omp_sched_static;
    int chunk_size = 0;

    switch (scheduleType) {
        case 1:
            break;
        case 2:
            schedule_kind = omp_sched_dynamic;
            break;
        case 3:
            chunk_size = CHUNK_SIZE;
            break;
        case 4:
            schedule_kind = omp_sched_dynamic;
            chunk_size = CHUNK_SIZE;
            break;
        default:
            std::cout << "Invalid scheduling type. Use 1-4.\n";
            std::cout << "1: static, 2: dynamic, 3: static with chunk size, 4: dynamic with chunk size\n" << "\n";
            return 1;
    }

    omp_set_schedule(schedule_kind, chunk_size);

    int count = 0;
    double start = omp_get_wtime();

#pragma omp parallel for reduction(+ : count) schedule(runtime) default(none)
    for (int i = 1; i <= MAX_NUM; ++i) {
        if (is_prime(i) != 0) {
            count++;
        }
    }

    double end = omp_get_wtime();
    std::cout << "Number of primes between 1 and " << MAX_NUM << ": " << count << "\n";
    std::cout << "Execution time: " << end - start << " seconds using " << numThreads << " threads (schedule type "
              << scheduleType << ")\n";

    return 0;
}
