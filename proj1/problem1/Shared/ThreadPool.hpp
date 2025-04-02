/*
** File: ThreadPool.hpp                                                        *
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

#include <vector>
#include "Thread.hpp"
#include <type_traits>

namespace Shared {
    template<typename T>
    concept ThreadConcept = std::is_base_of_v<Thread, T>;

    template<ThreadConcept T>
    class ThreadPool
    {
        private:
            int _numThreads;
            std::vector<T> _threads;

        public:
            explicit ThreadPool(int numThreads, int endNbr)
                : _numThreads(numThreads)
            {
                int range = endNbr / numThreads;

                for (int i = 0; i < numThreads; ++i) {
                    int startNbr = i * range;
                    int endNbr = ((i + 1) * range) - 1;

                    _threads.emplace_back(T(i, startNbr, endNbr));
                }
            }

            ~ThreadPool()
            {
                for (auto &thread : _threads) {
                    thread.join();
                }
            }

            void run()
            {
                for (auto &thread : _threads) {
                    thread.start();
                }

                for (auto &thread : _threads) {
                    thread.join();
                }
            }
    };
} // namespace Shared
