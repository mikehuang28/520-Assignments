#ifndef __TARGET_AGENT__H
#define __TARGET_AGENT__H

#include "enviro.h"

using namespace enviro;

class TargetController : public Process, public AgentInterface {
public:
    TargetController() : Process(), AgentInterface() {}
    void init() {
        // target be hit by projectile
        notice_collisions_with("Projectile", [&](Event &e) {
            remove_agent(id()); // Remove target
        });
    }
    void start() {}
    void update() {
        // speed -50 to 50
        double vx = (rand() % 100) - 50;
        double vy = (rand() % 100) - 50;
        track_velocity(vx, vy);

        // prevemt colliding with robot
        if (y() >= 120) {
            // std::cout << "Bounce up!! y: " << y() << ", Target ID: "<< id() << std::endl;
            // track_velocity(vx, -abs(vy)); // Bounce up
            vy = -abs(vy);
            teleport(x(), 115, 0); //relocate position
        }

        // Bounce back if hitting boundaries
        if (y() < -180 || x() < -320 || x() > 320) {
            track_velocity(-vx, -vy);
        }
    }
    void stop() {}
};

class Target : public Agent {
public:
    Target(json spec, World& world) : Agent(spec, world) {
        add_process(tc);
    }
private:
    TargetController tc;
};

DECLARE_INTERFACE(Target)

#endif