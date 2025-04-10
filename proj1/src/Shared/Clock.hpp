/*
** File: Clock.hpp                                                             *
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

#include <chrono>

namespace Shared {
    class Clock
    {
        protected:
            std::chrono::high_resolution_clock::time_point _startTime;

        public:
#pragma region constructor/destructor
            Clock() = default;
            ~Clock() = default;

            Clock(const Clock &other) = default;
            Clock &operator=(const Clock &other) = default;

            Clock(Clock &&other) noexcept = default;
            Clock &operator=(Clock &&other) noexcept = default;
#pragma endregion constructor / destructor

#pragma region methods

            /**
             * @brief Get the time elapsed since the last call to restart
             *
             * @return the time elapsed since the last call to restart
             */
            [[nodiscard]] auto getElapsedTime() const -> long;

            /**
             * @brief Start the clock
             *
             */
            void start();
#pragma endregion methods
    };
} // namespace Shared
