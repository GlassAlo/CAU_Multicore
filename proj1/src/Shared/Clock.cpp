/*
** File: Clock.cpp                                                             *
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

#include "Clock.hpp"

namespace Shared {
    auto Clock::getElapsedTime() const -> double
    {
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsedTime = endTime - _startTime;

        return elapsedTime.count();
    }

    void Clock::start()
    {
        _startTime = std::chrono::high_resolution_clock::now();
    }
} // namespace Shared
