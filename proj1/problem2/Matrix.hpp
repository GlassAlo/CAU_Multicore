/*
** File: Matric.hpp                                                            *
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

#include <ostream>
#include <vector>

namespace MatrixMultiplier {
    using row = std::vector<int>;

    class Matrix
    {
        private:
            std::vector<row> _matrix;
            int _nbrThreads;

        public:
            Matrix() = default;
            Matrix(int rows, int cols, int nbrThreads);
            Matrix(const Matrix &aMatrix) = default;
            Matrix(Matrix &&aMatrix) noexcept = default;
            auto operator=(const Matrix &aMatrix) -> Matrix & = default;
            auto operator=(Matrix &&aMatrix) noexcept -> Matrix & = default;

            auto operator*(const Matrix &aMatrix) -> Matrix;

            ~Matrix() = default;

            [[nodiscard]] auto getRows() const -> int;
            [[nodiscard]] auto getCols() const -> int;
            [[nodiscard]] auto getMatrix() const -> const std::vector<row> &;

            auto at(int row, int col) -> int &;
            [[nodiscard]] auto at(int row, int col) const -> const int &;

            static auto readMatrix(int nbrThreads) -> Matrix;
            auto print() const -> void;
            [[nodiscard]] auto getSum() const -> int;

            static auto getResultMatrix(int rows = 0, int cols = 0, int nbrThreads = 0) -> Matrix &
            {
                static Matrix result(rows, cols, nbrThreads);

                return result;
            } // for testing purpose
    };

    auto operator<<(std::ostream &ost, const Matrix &aMatrix) -> std::ostream &;

} // namespace MatrixMultiplier