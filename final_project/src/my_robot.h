#ifndef __ROBOT_AGENT__H
#define __ROBOT_AGENT__H

#include "enviro.h"

using namespace enviro;

class RobotController : public Process, public AgentInterface {
public:
    RobotController() : Process(), AgentInterface(), firing(false), LEFT(false), RIGHT(false), targets_remaining(5) {}

    void init() {

        prevent_rotation();

        // targets_remaining = count_targets();
        std::cout << "Initial targets: " << targets_remaining << std::endl;

        watch("target_hit", [&](Event &e) {
            remove_agent(e.value()["id"]); // Remove the hit target
            targets_remaining--; // decrease targets_remaining
            std::cout << "Targets remaining: " << targets_remaining << std::endl;
            check_win();
        });

        watch("keydown", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if (k == "k" && !firing) {
                // add projectiles to the game
                Agent& bullet = add_agent("Projectile", x(), y() - 17, 0, {});
                bullet.omni_track_velocity(0, -10, 10); // Straight upward
                firing = true;
            } else if (k == "a") {
                LEFT = true;
            } else if (k == "d") {
                RIGHT = true;
            }
        });
        watch("keyup", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if (k == "k") {
                firing = false;
            }
            else if (k == "a") {
                LEFT = false;
            }
            else if (k == "d") {
                RIGHT = false;
            }
        });
    }

    void start() {}

    void update() {
        double vx = 0; // Target x-velocity
        if (RIGHT && !LEFT) {
            vx = VEL_X; // Move right
        } else if (LEFT && !RIGHT) {
            vx = -VEL_X; // Move left
        }
        // Proportional force for smooth horizontal movement
        double fx = -K_X * (velocity().x - vx);
        omni_apply_force(fx, 0); // Apply force only in x-direction

        if (x() <= -320) { // Left boundary
            teleport(-320, 180, 0);
            vx = 0;
        } else if (x() >= 320) { // Right boundary
            teleport(320, 180, 0);
            vx = 0;
        }

        // Print position and velocity for debugging
        // std::cout << "Robot position: x=" << x() << ", y=" << y() << ", vx=" << velocity().x << std::endl;
    }

    void stop() {}

private:
    bool firing, LEFT, RIGHT;
    const double VEL_X = 50; // Max horizontal speed
    const double K_X = 15;    // Proportional gain for force
    int targets_remaining; // default = 5

    //check win conditions
    void check_win() {
        if (targets_remaining == 0) {
            label("You Win!", 50, 0); // display
            std::cout << "You win!" << std::endl;
        }
    }
};

class Robot : public Agent {
public:
    Robot(json spec, World& world) : Agent(spec, world) {
        add_process(rc);
    }
private:
    RobotController rc;
};

DECLARE_INTERFACE(Robot)

#endif