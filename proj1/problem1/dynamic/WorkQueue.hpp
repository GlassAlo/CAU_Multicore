/*
** File: WorkQueue.hpp                                                         *
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

#pragma once

#include <mutex>
#include <queue>

namespace Dynamic {
    class WorkQueue
    {
        private:
            std::queue<std::tuple<int, int>> _workQueue;
            std::mutex _mutex;

        public:
            WorkQueue() = default;
            ~WorkQueue() = default;

            WorkQueue(const WorkQueue &) = delete;
            WorkQueue(WorkQueue &&) noexcept = delete;
            auto operator=(const WorkQueue &) -> WorkQueue & = delete;
            auto operator=(WorkQueue &&) noexcept -> WorkQueue & = delete;

            void push(std::tuple<int, int> range);
            bool pop(std::tuple<int, int> &range);
    };
} // namespace Dynamic
