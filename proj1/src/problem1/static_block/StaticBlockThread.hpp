/*
** File: StaticBlockThread.hpp                                                 *
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

#pragma once

#include "Thread.hpp"

namespace StaticBlock {
    class StaticBlockThread : public Shared::Thread
    {
        private:
            int _startNbr;
            int _endNbr;

        public:
            StaticBlockThread(int idx, std::tuple<int, int> &Args);
            ~StaticBlockThread() override = default;

            StaticBlockThread(const StaticBlockThread &) = default;
            StaticBlockThread(StaticBlockThread &&) noexcept = default;
            auto operator=(const StaticBlockThread &) -> StaticBlockThread & = default;
            auto operator=(StaticBlockThread &&) noexcept -> StaticBlockThread & = default;

            void run() override;
    };
} // namespace StaticBlock