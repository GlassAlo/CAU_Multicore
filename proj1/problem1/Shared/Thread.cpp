/*
** File: Thread.cpp                                                            *
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

#include "Thread.hpp"

namespace Shared {
    Thread::Thread(int idx)
        : _idx(idx)
    {}

    Thread::Thread(const Thread &other)
        : _idx(other._idx)
    {}

    Thread::Thread(Thread &&other) noexcept
        : _idx(other._idx)
    {
        other._thread = std::thread();
    }

    auto Thread::operator=(const Thread &other) -> Thread &
    {
        if (this != &other) {
            _idx = other._idx;
        }
        return *this;
    }

    auto Thread::operator=(Thread &&other) noexcept -> Thread &
    {
        if (this != &other) {
            _idx = other._idx;
            other._thread = std::thread();
        }
        return *this;
    }

    void Thread::run()
    {}

    void Thread::start()
    {
        _thread = std::thread(&Thread::run, this);
    }

    void Thread::join()
    {
        if (_thread.joinable()) {
            _thread.join();
        }
    }
} // namespace Shared
