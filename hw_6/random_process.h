#ifndef RANDOM_PROCESS_H
#define RANDOM_PROCESS_H

#include <random>
#include "elma/elma.h"

using namespace elma;

class RandomProcess : public Process {
    private:
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<double> dist;

    public:
        RandomProcess(std::string name) : Process(name) {
            gen = std::mt19937(rd());
            dist = std::uniform_real_distribution<double>(0.0, 1.0);
        }

        void init() {}
        void start() {}
        void update() {
            double random_value = dist(gen); // random value from 0 to 1
            channel("link").send(random_value);
        }
        void stop() {}
};

#endif // RANDOM_PROCESS_H