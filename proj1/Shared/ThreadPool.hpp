/*
** File: ThreadPool.hpp                                                        *
** Project: static_block                                                       *
** Created Date: We Apr 2025                                                   *
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

#pragma once

#include <vector>
#include "Thread.hpp"
#include <type_traits>

namespace Shared {
    template<typename T>
    concept ThreadConcept = std::is_base_of_v<Thread, T>;

    template<typename T>
    concept ThreadContainerConcept = requires(T t) {
        typename T::value_type;
        std::begin(t);
        std::end(t);
    };

    template<ThreadConcept T>
    class ThreadPool
    {
        private:
            int _numThreads;
            std::vector<T> _threads;

            template<typename Arg>
            void createOneThread(int idx, Arg &&arg)
            {
                _threads.emplace_back(T(idx, std::forward<Arg>(arg)));
            }

        public:
            template<ThreadContainerConcept Container>
            explicit ThreadPool(int numThreads, Container &&argsContainer)
                : _numThreads(numThreads)
            {
                auto tmp = std::forward<Container>(argsContainer);
                _threads.reserve(numThreads);
                auto itx = std::begin(tmp);
                auto size = std::distance(itx, std::end(tmp));

                for (int i = 0; i < numThreads; ++i, itx++) {
                    if (itx == std::end(tmp)) {
                        throw std::runtime_error("Not enough arguments in container!");
                    }
                    if (size == 1) {
                        itx = std::begin(tmp);
                    }
                    createOneThread(i, *itx);
                }
            }

            template<typename... Args>
            explicit ThreadPool(int numThreads, Args &&...args)
                : _numThreads(numThreads)
            {
                _threads.reserve(numThreads);
                for (int i = 0; i < numThreads; ++i) {
                    createOneThread(i, std::forward<Args>(args)...);
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
