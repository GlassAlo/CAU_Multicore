/*
** File: StaticCyclicThread.hpp                                                *
** Project: static_cyclic                                                      *
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

#pragma once

#include <vector>
#include "Thread.hpp"

namespace StaticCyclic {
    class StaticCyclicThread : public Shared::Thread
    {
        private:
            std::vector<std::tuple<int, int>> _ranges;

        public:
            StaticCyclicThread(int idx, std::vector<std::tuple<int, int>> &Args);
            ~StaticCyclicThread() override = default;

            StaticCyclicThread(const StaticCyclicThread &) = default;
            StaticCyclicThread(StaticCyclicThread &&) noexcept = default;
            auto operator=(const StaticCyclicThread &) -> StaticCyclicThread & = default;
            auto operator=(StaticCyclicThread &&) noexcept -> StaticCyclicThread & = default;

            void run() override;
    };
} // namespace StaticCyclic
