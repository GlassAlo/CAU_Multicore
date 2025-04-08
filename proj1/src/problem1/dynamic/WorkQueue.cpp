/*
** File: WorkQueue.cpp                                                         *
** Project: dynamic                                                            *
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

#include "WorkQueue.hpp"

namespace Dynamic {
    void WorkQueue::push(std::tuple<int, int> range)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _workQueue.push(range);
    }

    auto WorkQueue::pop(std::tuple<int, int> &range) -> bool
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_workQueue.empty()) {
            return false;
        }
        range = _workQueue.front();
        _workQueue.pop();
        return true;
    }
} // namespace Dynamic
