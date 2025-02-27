#include "stopwatch.h"

Stopwatch::Stopwatch() {
    reset();
}

void Stopwatch::start() {
    if (!running) {
        start_time = std::chrono::high_resolution_clock::now();
        running = true;
    }
}

void Stopwatch::stop() {
    if (running) {
        stop_time = std::chrono::high_resolution_clock::now();
        elapsed += std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time - start_time);
        running = false;
    }
}

void Stopwatch::reset() {
    elapsed = std::chrono::nanoseconds::zero();
    running = false;
}

double Stopwatch::get_minutes() {
    return get_nanoseconds() / (60 * 1e9);
}

double Stopwatch::get_seconds() {
    return get_nanoseconds() / 1e9;
}

double Stopwatch::get_milliseconds() {
    return get_nanoseconds() / 1e6;
}

double Stopwatch::get_nanoseconds() {
    if (running) {
        auto current_time = std::chrono::high_resolution_clock::now();
        return static_cast<double>((elapsed + std::chrono::duration_cast<std::chrono::nanoseconds>(current_time - start_time)).count());
    } else {
        return static_cast<double>(elapsed.count());
    }
}