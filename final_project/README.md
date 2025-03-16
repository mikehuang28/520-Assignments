# EEP520 Final Project

## Project Overview
This project is a shooting game built with `enviro` framework, where a player-controlled robot shoots projectiles to eliminate moving targets. The goal is to demonstrate basic game mechanics, including collision detection, boundary enforcement, and a win condition. When all targets are hit, "You Win!" appears on the screen.

## Key Challenges and Solutions
- **Target-Robot Collision**: Targets initially could collide with the robot, causing the robot to rotate. This was addressed by restricting target y-coordinates using velocity reversal and teleportation.
- **Event Detection**: The `"target_hit"` event wasn’t triggering consistently. Resolved by ensuring `Projectile` emits the event with the target’s ID  and `RobotController` watches it correctly.

## Operation Description
### How to run the code
1. Clone the Repository
    ```bash
    git clone <repo-url>
    cd existing_repo
    ```

2. Run `esm` as follows
    ```bash
    esm init
    esm start
    ```

3. Run Makefile
   ```bash
   make
   enviro
   ```
4. Open ``http://localhost/`` with the web browser. You can press `Ctrl-C` to stop the `enviro` server.

### How to play the game
Once the simulation is running at ``http://localhost/``:

- **Elements on the screen**
  - **My Robot** (blue)
  - **Targets** (red)
  - **Blocks** (yellow)
  - **Projectiles** (white)

- **Controls**
  - **Move Left**: Press `a` to move the robot left
  - **Move Right**: Press `d` to move the robot right
  - **Shoot**: Press `k` to fire a projectile upward

- **Gameplay**
  - The robot starts at botom middle of the screen
  - Number of targets is 5 by default
  - Hit all targets with projectiles to win
  - When all targets are destroyed, "You Win!" appears next to the robot


## Acknowledgements

- [Enviro](https://github.com/klavinslab/enviro)
- [Enviro Examples](https://github.com/klavinslab/enviro/tree/master/examples)
- [Shooting Game in C++](https://github.com/B16CS006/The_Ultimate_Shootng_Challenge)
- [Docker](https://www.docker.com/)
- [Docker Commands](https://docs.docker.com/get-started/docker_cheatsheet.pdf)
