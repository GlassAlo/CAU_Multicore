/*
** File: MatrixThread.cpp                                                      *
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

#include "MatrixThread.hpp"
#include <syncstream>
#include "Matrix.hpp"

namespace MatrixMultiplier {
    MatrixThread::MatrixThread(int idx, rangesAndMatrices &aArgs)
        : Shared::Thread(idx),
          _ranges(std::move(aArgs.first)),
          _firstMatrix(std::get<0>(aArgs.second)),
          _secondMatrix(std::get<1>(aArgs.second))
    {}

    void MatrixThread::run()
    {
        Matrix &resultMatrix = Matrix::getResultMatrix();

        _clock.start();
        for (const auto &[startRow, endRow] : _ranges) {
            for (int i = startRow; i < endRow; ++i) {
                for (int j = 0; j < _secondMatrix.getCols(); ++j) {
                    for (int k = 0; k < _firstMatrix.getCols(); ++k) {
                        resultMatrix.at(i, j) += _firstMatrix.at(i, k) * _secondMatrix.at(k, j);
                    }
                }
            }
        }
        auto elapsedTimeInMs = _clock.getElapsedTime();

        std::osyncstream(std::cout) << "Thread " << _idx << " Execution Time: " << elapsedTimeInMs << " ms"
                                    << "\n";
    }
} // namespace MatrixMultiplier