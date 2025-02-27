#ifndef FILTER_H
#define FILTER_H

#include <deque>
#include "elma/elma.h"

using namespace elma;

class Filter : public Process {
    private:
        std::deque<double> values;
        double running_avg;

    public:
        Filter(std::string name) : Process(name), running_avg(0) {}

        void init() {}
        void start() {}
        void update() {
            if (channel("link").empty()) {
                return;
            }

            // Read from the link channel
            double input = channel("link").latest();

            // Add to our collection
            values.push_back(input);

            // Keep only the last 10 values
            if (values.size() > 10) {
                values.pop_front();
            }

            // Calculate running average
            running_avg = 0;
            for (double v : values) {
                running_avg += v;
            }
            running_avg /= values.size();
        }

        void stop() {}

        // Return the current running average
        double value() {
            return running_avg;
        }
};

#endif // FILTER_H