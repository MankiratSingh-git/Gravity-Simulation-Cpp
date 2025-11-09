#include <iostream>
#include <iomanip>
#include <cmath>
#include "../include/simulation.hpp"

static const int M_PI = 3.14159265359;

int main() {
  Simulation sim(1.0, 100);
  double m = 1;
  double R = 100;
  double v = std::sqrt((sim.G * m) / (std::sqrt(3.0) * R)); 

  Body A("A", m, Vec2(R, 0), Vec2(0, v));
  Body B("B", m, Vec2(-R / 2, R * std::sqrt(3) / 2), Vec2(-v * std::sqrt(3) / 2, -v / 2));
  Body C("C", m, Vec2(-R / 2, -R * std::sqrt(3) / 2), Vec2(v * std::sqrt(3) / 2, -v / 2));

  sim.bodies = {A, B, C};

  double dt = 0.1;
  int steps = 100000;

  std::cout << std::fixed << std::setprecision(3);


  std::cout << std::setw(8)  << "t"
            << std::setw(12) << "A.x"
            << std::setw(12) << "A.y"
            << std::setw(12) << "B.x"
            << std::setw(12) << "B.y"
            << std::setw(12) << "C.x"
            << std::setw(12) << "C.y"
            << std::setw(12) << "distAB"
            << std::setw(12) << "distBC"
            << std::setw(12) << "distCA"
            << "\n";
  std::cout << std::string(120, '-') << "\n";


  for (int step = 0; step <= steps; ++step) {
    sim.step(dt);

    Body& Aref = sim.bodies[0];
    Body& Bref = sim.bodies[1];
    Body& Cref = sim.bodies[2];

    double distAB = (Aref.pos - Bref.pos).length();
    double distBC = (Bref.pos - Cref.pos).length();
    double distCA = (Cref.pos - Aref.pos).length();

  if (step % 100 == 0) {
    std::cout << std::setw(8)  << sim.time
              << std::setw(12) << Aref.pos.x
              << std::setw(12) << Aref.pos.y
              << std::setw(12) << Bref.pos.x
              << std::setw(12) << Bref.pos.y
              << std::setw(12) << Cref.pos.x
              << std::setw(12) << Cref.pos.y
              << std::setw(12) << distAB
              << std::setw(12) << distBC
              << std::setw(12) << distCA
              << "\n";
    }
  }
  std::cout << "Simulation done!" << std::endl;
  system("pause");  // Waits for a keypress
  return 0;
  }
