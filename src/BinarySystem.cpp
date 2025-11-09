#include <iostream>
#include <iomanip>
#include "../include/simulation.hpp"

int main() {
    Simulation sim;
    sim.G = 1.0;
    sim.scale = 100;


    Body bodyA("A", 1.0, Vec2(50, 0), Vec2(0, 0.0707107));
    Body bodyB("B", 1.0, Vec2(-50, 0), Vec2(0, -0.0707107));

    sim.bodies.push_back(bodyA);
    sim.bodies.push_back(bodyB);

    double dt = 0.1;
    int steps = 100000;

    std::cout << std::fixed << std::setprecision(3);

    // Print table header
    std::cout << std::setw(8)  << "t"
                << std::setw(12) << "A.x"
                << std::setw(12) << "A.y"
                << std::setw(12) << "A.vx"
                << std::setw(12) << "A.vy"
                << std::setw(12) << "B.x"
                << std::setw(12) << "B.y"
                << std::setw(12) << "B.vx"
                << std::setw(12) << "B.vy"
                << std::setw(12) << "dist"
                << "\n";

    std::cout << std::string(120, '-') << "\n";

    for (int step = 0; step <= steps; ++step) {
        sim.step(dt);

        Body& A = sim.bodies[0];
        Body& B = sim.bodies[1];

        Vec2 distVec = A.pos - B.pos;
        double dist = distVec.length();

        // Print every 100 steps
        if (step % 100 == 0) {
            std::cout << std::setw(8)  << sim.time
                        << std::setw(12) << A.pos.x
                        << std::setw(12) << A.pos.y
                        << std::setw(12) << A.vel.x
                        << std::setw(12) << A.vel.y
                        << std::setw(12) << B.pos.x
                        << std::setw(12) << B.pos.y
                        << std::setw(12) << B.vel.x
                        << std::setw(12) << B.vel.y
                        << std::setw(12) << dist
                        << "\n";
        }
    }

    std::cout << "Simulation done!" << std::endl;
    system("pause");  // Waits for a keypress
    return 0;
}
