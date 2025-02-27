#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

class Stopwatch {
    private:
        std::chrono::high_resolution_clock::time_point start_time;
        std::chrono::high_resolution_clock::time_point stop_time;
        bool running;
        std::chrono::nanoseconds elapsed;

    public:
        // Constructor
        Stopwatch();

        // Methods
        void start();
        void stop();
        void reset();

        double get_minutes();
        double get_seconds();
        double get_milliseconds();
        double get_nanoseconds();
};

#endif // STOPWATCH_H