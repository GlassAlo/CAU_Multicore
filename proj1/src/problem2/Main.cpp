/*
** File: Main.cpp                                                              *
** Project: problem2                                                           *
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

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "Clock.hpp"
#include "Matrix.hpp"

int main(int argc, char *argv[])
{
    int thread_no = 1;
    Shared::Clock clock;

    if (argc == 2) {
        thread_no = std::atoi(argv[1]);
    }

    MatrixMultiplier::Matrix firstMatrix = MatrixMultiplier::Matrix::readMatrix(thread_no);
    MatrixMultiplier::Matrix secondMatrix = MatrixMultiplier::Matrix::readMatrix(thread_no);

    clock.start();
    MatrixMultiplier::Matrix resultMatrix = firstMatrix * secondMatrix;
    auto duration = clock.getElapsedTime();

    std::cout << "Sum of the result matrix: " << resultMatrix.getSum() << "\n";

    std::cout << "[thread_no]:" << std::setw(2) << thread_no << " , [Time]:" << std::setw(4) << duration << " ms\n";

    return 0;
}
