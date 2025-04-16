/*
** File: Matrix.cpp                                                            *
** Project: problem2                                                           *
** Created Date: Tu Apr 2025                                                   *
** Author: GlassAlo                                                            *
** Email: ofourpatat@gmail.com                                                 *
** -----                                                                       *
** Description: {Enter a description for the file}                             *
** -----                                                                       *
** Last Modified: Tue Apr 15 2025                                              *
** Modified By: GlassAlo                                                       *
** -----                                                                       *
** Copyright (c) 2025 Aurea-Games                                              *
** -----                                                                       *
** HISTORY:                                                                    *
** Date      	By	Comments                                                   *
** ----------	---	---------------------------------------------------------  *
*/

#include "Matrix.hpp"
#include <iomanip>
#include <iostream>
#include "MatrixThread.hpp"
#include "ThreadPool.hpp"

namespace MatrixMultiplier {
    Matrix::Matrix(int rows, int cols, int nbrThreads)
        : _matrix(rows, row(cols)),
          _nbrThreads(nbrThreads)
    {}

    auto Matrix::operator*(const Matrix &aMatrix) -> Matrix
    {
        int rows = getRows();
        int cols = aMatrix.getCols();
        getResultMatrix(rows, cols, _nbrThreads);
        rangesAndMatricesFull threadsRanges(_nbrThreads);
        threadsRanges.reserve(_nbrThreads);

        int rowsPerThread = rows / _nbrThreads;
        int remainingRows = rows % _nbrThreads;
        int startRow = 0;

        for (int i = 0; i < _nbrThreads; i++) {
            int endRow = startRow + rowsPerThread + (i < remainingRows ? 1 : 0);

            threadsRanges[i].first.emplace_back(startRow, endRow);
            threadsRanges[i].second = std::make_tuple(*this, aMatrix);
            startRow = endRow;
        }

        // Create a thread pool and run the threads
        Shared::ThreadPool<MatrixThread> threadPool(_nbrThreads, std::move(threadsRanges));
        threadPool.run();

        return getResultMatrix();
    }

    auto Matrix::readMatrix(int aNbrThreads) -> Matrix
    {
        int rows = 0;
        int cols = 0;

        std::cin >> rows >> cols;
        Matrix mat(rows, cols, aNbrThreads);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cin >> mat.at(i, j);
            }
        }
        return mat;
    }

    auto Matrix::print() const -> void
    {
        std::cout << *this;
    }

    auto Matrix::getRows() const -> int
    {
        return static_cast<int>(_matrix.size());
    }

    auto Matrix::getCols() const -> int
    {
        return static_cast<int>(_matrix[0].size());
    }

    auto Matrix::getMatrix() const -> const std::vector<row> &
    {
        return _matrix;
    }

    auto Matrix::at(int row, int col) -> int &
    {
        return _matrix[row][col];
    }

    auto Matrix::at(int row, int col) const -> const int &
    {
        return _matrix[row][col];
    }

    auto Matrix::getSum() const -> int
    {
        int sum = 0;

        for (const auto &row : _matrix) {
            for (int val : row) {
                sum += val;
            }
        }
        return sum;
    }

    auto operator<<(std::ostream &ost, const Matrix &aMatrix) -> std::ostream &
    {
        int rows = aMatrix.getRows();
        int cols = aMatrix.getCols();

        ost << "Matrix[" << rows << "][" << cols << "]\n";
        for (const auto &row : aMatrix.getMatrix()) {
            for (int val : row) {
                ost << std::setw(4) << val << " ";
            }
            ost << '\n';
        }
        return ost;
    }
} // namespace MatrixMultiplier
