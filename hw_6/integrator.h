#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "elma/elma.h"

using namespace elma;

class Integrator : public Process {
    private:
        double integral_value;

    public:
        Integrator(std::string name) : Process(name), integral_value(0) {}

        void init() {}
        void start() {}
        // void update() {
        //     if (channel("link").empty()) {
        //         return;
        //     }

        //     // Read from the link channel
        //     double input = channel("link").latest();

        //     // delta() already returns time in seconds
        //     double dt = delta();

        //     // Add the delta * input to the integral
        //     integral_value += dt * input;
        // }

        void update() {
            if (channel("link").empty()) {
                return;
            }

            double input = channel("link").latest();

            // Correct conversion from milliseconds to seconds
            double delta_in_seconds = delta() / 1000.0;

            integral_value += delta_in_seconds * input;
        }


        void stop() {}

        // Return the current integral value
        double value() {
            return integral_value;
        }
};

#endif // INTEGRATOR_H