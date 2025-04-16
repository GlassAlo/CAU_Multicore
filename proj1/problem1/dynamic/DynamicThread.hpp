/*
** File: DynamicThread.hpp                                                *
** Project: dynamic                                                      *
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

#include <functional>
#include <vector>
#include "Thread.hpp"
#include "WorkQueue.hpp"

namespace Dynamic {
    class DynamicThread : public Shared::Thread
    {
        private:
            std::reference_wrapper<WorkQueue> _workQueue;

        public:
            explicit DynamicThread(int idx, WorkQueue &workQueue);
            ~DynamicThread() override = default;

            DynamicThread(const DynamicThread &) = default;
            DynamicThread(DynamicThread &&) noexcept = default;
            auto operator=(const DynamicThread &) -> DynamicThread & = default;
            auto operator=(DynamicThread &&) noexcept -> DynamicThread & = default;

            void run() override;
    };
} // namespace Dynamic
