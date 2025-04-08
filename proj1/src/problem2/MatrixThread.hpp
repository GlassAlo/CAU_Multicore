/*
** File: MatrixThread.hpp                                                      *
** Project: problem2                                                           *
** Created Date: Tu Apr 2025                                                   *
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

#include <functional>
#include <tuple>
#include <utility>
#include "Matrix.hpp"
#include "Thread.hpp"

namespace MatrixMultiplier {
    using range = std::tuple<int, int>;
    using ranges = std::vector<range>;
    using Matrices = std::tuple<Matrix, Matrix>;
    using rangesAndMatricesFull = std::vector<std::pair<ranges, Matrices>>;
    using rangesAndMatrices = std::pair<ranges, Matrices>;

    class MatrixThread : public Shared::Thread
    {
        private:
            ranges _ranges;
            Matrix _firstMatrix;
            Matrix _secondMatrix;

        public:
            MatrixThread(int idx, rangesAndMatrices &Args);
            ~MatrixThread() override = default;

            MatrixThread(const MatrixThread &) = default;
            MatrixThread(MatrixThread &&) noexcept = default;
            auto operator=(const MatrixThread &) -> MatrixThread & = default;
            auto operator=(MatrixThread &&) noexcept -> MatrixThread & = default;

            void run() override;
    };
} // namespace MatrixMultiplier