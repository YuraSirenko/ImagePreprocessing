#ifndef CLOCK_H
#define CLOCK_H

#pragma once

#include <chrono>

class Clock {
public:
    using clock_t = std::chrono::steady_clock;
    using duration_t = std::chrono::duration<double, std::milli>;

    Clock() : running_{false}, elapsed_{duration_t::zero()} {
    }

    void start() {
        if (!running_) {
            start_time_ = clock_t::now();
            running_ = true;
        }
    }

    void stop() {
        if (running_) {
            elapsed_ += clock_t::now() - start_time_;
            running_ = false;
        }
    }

    void reset() {
        running_ = false;
        elapsed_ = duration_t::zero();
    }

    duration_t elapsed() const {
        if (running_) {
            return elapsed_ + (clock_t::now() - start_time_);
        }
        return elapsed_;
    }

    void logTime() const {
        std::cout << "Elapsed time: " << elapsed().count() << " ms\n";
    }

private:
    bool running_;
    clock_t::time_point start_time_;
    duration_t elapsed_;
};

#endif //CLOCK_H
