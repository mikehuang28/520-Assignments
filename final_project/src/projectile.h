#ifndef __projectile_AGENT__H
#define __projectile_AGENT__H

#include "enviro.h"

using namespace enviro;

class ProjectileController : public Process, public AgentInterface {
public:
    ProjectileController() : Process(), AgentInterface() {}
    void init() {

        // hit target
        notice_collisions_with("Target", [&](Event &e) {
            // std::cout << "Hit the target, target ID: " << e.value()["id"] << std::endl;
            remove_agent(id());
            emit(Event("target_hit", {{"id", e.value()["id"]}})); // Emit event
        });

        // hit block
        notice_collisions_with("Block", [&](Event &e) {
            remove_agent(id());
        });

    }
    void start() {}
    void update() {

        // debug
        // std::cout << "Bullet position: x=" << x() << ", y=" << y() << ", Bullet speed: vx=" << vx() << ", vy=" << vy() << std::endl;

        if (y() <= -180 || y() >= 180 || x() <= -330 || x() >= 330) { // Hits walls
            remove_agent(id());
        }

    }
    void stop() {}
};

class Projectile : public Agent {
public:
    Projectile(json spec, World& world) : Agent(spec, world) {
        add_process(pc);
    }
private:
    ProjectileController pc;
};

DECLARE_INTERFACE(Projectile)

#endif