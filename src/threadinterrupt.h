// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2018-2025 The Verge Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef VERGE_THREADINTERRUPT_H
#define VERGE_THREADINTERRUPT_H

#include <sync.h>

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>

/*
    A helper class for interruptible sleeps. Calling operator() will interrupt
    any current sleep, and after that point operator bool() will return true
    until reset.
*/
class CThreadInterrupt
{
public:
    CThreadInterrupt();
    explicit operator bool() const;
    void operator()();
    void reset();
    bool sleep_for(std::chrono::milliseconds rel_time);
    bool sleep_for(std::chrono::seconds rel_time);
    bool sleep_for(std::chrono::minutes rel_time);

private:
    std::condition_variable cond;
    Mutex mut;
    std::atomic<bool> flag;
};

#endif //VERGE_THREADINTERRUPT_H
