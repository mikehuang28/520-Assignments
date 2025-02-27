#include <iostream>
#include <cassert>
#include <cmath>
#include <thread>
#include <chrono>
#include "elma/elma.h"
#include "stopwatch.h"
#include "random_process.h"
#include "filter.h"
#include "integrator.h"
#include <gtest/gtest.h>



#define SLEEP(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))

namespace {

    using namespace elma;

    // Stopwatch Tests
    TEST(Stopwatch, Construction) {
        Stopwatch sw;
        ASSERT_NEAR(sw.get_seconds(), 0.0, 0.001);
    }

    TEST(Stopwatch, StartStop) {
        Stopwatch sw;
        sw.start();
        SLEEP(100);
        sw.stop();
        ASSERT_NEAR(sw.get_milliseconds(), 100.0, 20.0);
    }

    TEST(Stopwatch, Reset) {
        Stopwatch sw;
        sw.start();
        SLEEP(100);
        sw.stop();
        sw.reset();
        ASSERT_NEAR(sw.get_seconds(), 0.0, 0.001);
    }

    TEST(Stopwatch, Paused) {
        Stopwatch sw;
        sw.start();
        SLEEP(100);
        sw.stop();
        double time = sw.get_milliseconds();
        SLEEP(50);
        // Time should not have changed after stopping
        ASSERT_NEAR(sw.get_milliseconds(), time, 0.001);
    }

    TEST(Stopwatch, Accumulation) {
        Stopwatch sw;
        sw.start();
        SLEEP(100);
        sw.stop();
        sw.start();
        SLEEP(100);
        sw.stop();
        // Should be approximately 200ms
        ASSERT_NEAR(sw.get_milliseconds(), 200.0, 30.0);
    }

    TEST(Stopwatch, UnitConversions) {
        Stopwatch sw;
        sw.start();
        SLEEP(500);
        sw.stop();
        // Test various time unit conversions
        ASSERT_NEAR(sw.get_seconds(), 0.5, 0.05);
        ASSERT_NEAR(sw.get_milliseconds(), 500.0, 50.0);
        ASSERT_NEAR(sw.get_minutes(), 0.5/60.0, 0.001);
        // Nanoseconds will be approximately 500,000,000
        ASSERT_NEAR(sw.get_nanoseconds(), 500000000, 50000000);
    }


    // Filter Tests
    TEST(Filter, RunningAverage) {
        Manager m;
        Channel link("link");

        // Custom process that alternates between 0.25 and 0.75
        class AlternatingProcess : public Process {
            private:
                bool toggle;

            public:
                AlternatingProcess() : Process("alternating"), toggle(false) {}

                void init() {}
                void start() {}
                void update() {
                    toggle = !toggle;
                    channel("link").send(toggle ? 0.75 : 0.25);
                }
                void stop() {}
        };

        AlternatingProcess ap;
        Filter f("filter");

        m.schedule(ap, 1_ms)
         .schedule(f, 1_ms)
         .add_channel(link)
         .init()
         .run(100_ms);

        // After 100 steps, average should be close to 0.5
        ASSERT_NEAR(f.value(), 0.5, 0.05);
    }

    TEST(Filter, InitialValue) {
        Filter f("filter");
        // Initial value should be 0
        ASSERT_EQ(f.value(), 0.0);
    }

    TEST(Filter, PartialBuffer) {
        Manager m;
        Channel link("link");

        // Process that sends fixed values
        class FixedValueProcess : public Process {
            private:
                double value;
                int count;

            public:
                FixedValueProcess(double v) : Process("fixed"), value(v), count(0) {}

                void init() {}
                void start() {}
                void update() {
                    if (count < 5) { // Only send 5 values
                        channel("link").send(value);
                        count++;
                    }
                }
                void stop() {}
        };

        FixedValueProcess fvp(2.0); // All values are 2.0
        Filter f("filter");

        m.schedule(fvp, 1_ms)
         .schedule(f, 1_ms)
         .add_channel(link)
         .init()
         .run(50_ms);

        // With 5 values all at 2.0, average should be 2.0
        ASSERT_NEAR(f.value(), 2.0, 0.001);
    }

    // Integrator Tests
    TEST(Integrator, ConstantValue) {
        Manager m;
        Channel link("link");

        class ConstantProcess : public Process {
            public:
                ConstantProcess() : Process("constant") {}
                void init() {}
                void start() {}
                void update() { channel("link").send(1.0); }
                void stop() {}
        };

        ConstantProcess cp;
        Integrator i("integrator");

        m.schedule(cp, 1_ms)
         .schedule(i, 1_ms)
         .add_channel(link)
         .init()
         .run(100_ms);

        // Integral of 1.0 over 100ms with 1ms steps should be close to 0.1
        ASSERT_NEAR(i.value(), 0.1, 0.01);
    }

    TEST(Integrator, Ramp) {
        Manager m;
        Channel link("link");

        // Process that sends linearly increasing values
        class RampProcess : public Process {
            private:
                double value;
                double increment;

            public:
                RampProcess(double start, double inc) :
                    Process("ramp"), value(start), increment(inc) {}

                void init() {}
                void start() {}
                void update() {
                    channel("link").send(value);
                    value += increment;
                }
                void stop() {}
        };

        // Start at 0, increment by 0.1 each step
        RampProcess rp(0.0, 0.1);
        Integrator i("integrator");

        m.schedule(rp, 1_ms)
         .schedule(i, 1_ms)
         .add_channel(link)
         .init()
         .run(100_ms);

        // Integral of ramp from 0 to 10 over 100ms should be around 0.5
        // (average value 5.0 * time 0.1s)
        ASSERT_NEAR(i.value(), 0.5, 0.05);
    }

    TEST(Integrator, InitialValue) {
        Integrator i("integrator");
        // Initial integral value should be 0
        ASSERT_EQ(i.value(), 0.0);
    }

    TEST(Integrator, SineWave) {
        Manager m;
        Channel link("link");

        // Process that sends sine wave values
        class SineProcess : public Process {
            private:
                double time;
                double frequency;

            public:
                SineProcess(double freq) : Process("sine"), time(0), frequency(freq) {}

                void init() {}
                void start() {}
                void update() {
                    double value = sin(2 * M_PI * frequency * time);
                    channel("link").send(value);
                    time += delta() / 1000.0; // Convert delta to seconds
                }
                void stop() {}
        };

        // 5Hz sine wave
        SineProcess sp(5.0);
        Integrator i("integrator");

        m.schedule(sp, 1_ms)
         .schedule(i, 1_ms)
         .add_channel(link)
         .init()
         .run(200_ms);

        // Integral of sine wave over complete cycles should be close to zero
        ASSERT_NEAR(i.value(), 0.0, 0.05);
    }

    // RandomProcess Tests
    TEST(RandomProcess, OutputRange) {
        Manager m;
        Channel link("link");

        RandomProcess rp("random");

        // Custom process to verify RandomProcess outputs
        class VerifierProcess : public Process {
            private:
                double min_value;
                double max_value;
                int count;

            public:
                VerifierProcess() :
                    Process("verifier"), min_value(1.0), max_value(0.0), count(0) {}

                void init() {}
                void start() {}
                void update() {
                    if (!channel("link").empty()) {
                        double val = channel("link").latest();
                        count++;
                        min_value = std::min(min_value, val);
                        max_value = std::max(max_value, val);
                    }
                }
                void stop() {}

                double get_min() { return min_value; }
                double get_max() { return max_value; }
                int get_count() { return count; }
        };

        VerifierProcess vp;

        m.schedule(rp, 1_ms)
         .schedule(vp, 1_ms)
         .add_channel(link)
         .init()
         .run(100_ms);

        // RandomProcess should produce values in [0,1]
        ASSERT_GE(vp.get_min(), 0.0);
        ASSERT_LE(vp.get_max(), 1.0);

        // Should have received multiple values
        ASSERT_GT(vp.get_count(), 50);
    }


}