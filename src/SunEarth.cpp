#include <iostream>
#include <iomanip>
#include "../include/simulation.hpp"

int main() {
    Simulation sim;
    sim.G = 1.0;
    sim.scale = 1000;

    Body sun("Sun", 1000.0, Vec2(0, 0), Vec2(0, 0));
    Body earth("Earth", 1.0, Vec2(100, 0), Vec2(0, 3.16));

    sim.bodies.push_back(sun);
    sim.bodies.push_back(earth);

    double dt = 0.01;
    int steps = 100000;

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "t\t\tEarth.x\tEarth.y\t\tvx\tvy\t\tdist\t\tFx\tFy\t|F|\n";

    for (int step = 0; step <= steps; ++step) {
        sim.step(dt);

        Body& sunRef   = sim.bodies[0];
        Body& earthRef = sim.bodies[1];


        Vec2 distVec = sunRef.pos - earthRef.pos;
        double dist = distVec.length();


        Vec2 unitDist = distVec / dist;
        double Fmag = sim.G * sunRef.mass * earthRef.mass
                    / (dist * dist + sim.s * sim.s);
        Vec2 Fvec = unitDist * (Fmag);


        if (step % 100 == 0) {
            std::cout << sim.time << "\t\t"
                      << earthRef.pos.x << "\t"
                      << earthRef.pos.y << "\t\t"
                      << earthRef.vel.x << "\t"
                      << earthRef.vel.y << "\t\t"
                      << dist << "\t\t"
                      << Fvec.x << "\t"
                      << Fvec.y << "\t"
                      << Fmag << "\n";
        }
    }

    return 0;
}
