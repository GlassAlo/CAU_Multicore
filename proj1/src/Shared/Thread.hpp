/*
** File: Thread.hpp                                                            *
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

#include <iostream>
#include <thread>
#include "Clock.hpp"

namespace Shared {
    class Clock;

    class Thread
    {
        protected:
            std::thread _thread;
            int _idx;
            Clock _clock;

        public:
            Thread(int idx);
            Thread(const Thread &);
            Thread(Thread &&) noexcept;
            auto operator=(const Thread &) -> Thread &;
            auto operator=(Thread &&) noexcept -> Thread &;

            virtual ~Thread() = default;

            virtual void run();

            void start();

            void join();
    };
} // namespace Shared
