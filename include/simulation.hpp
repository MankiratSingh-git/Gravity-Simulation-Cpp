#pragma once
#include<vector>
#include"body.hpp"

struct Simulation{
  std::vector<Body> bodies;
  double G;
  double time = 0;
  int scale;
  double s = 1e-4 * scale;

  Simulation(double G_ = 1.0, int scale_ = 1000): G(G_), scale(scale_) {}

  void step(double dt){

    for(Body& body : bodies){
      body.resetAcc();
    }

    for(int i = 0 ; i < bodies.size() ; ++i){
      for(int j = i+1 ; j < bodies.size() ; ++j){
        if(i==j) continue;
        Vec2 distVec = bodies[j].pos - bodies[i].pos;
        double dist = distVec.length();
        Vec2 unitDist = distVec / dist;
        if(dist < s) continue;
        double force = G*(bodies[i].mass)*(bodies[j].mass) / (dist*dist + s*s);
        Vec2 forceVec = unitDist * force;
        bodies[i].applyForce(forceVec);
        bodies[j].applyForce(-forceVec);
      }
    }

    for(Body& body : bodies){
      body.update(dt);
    }
    time += dt;
  }
};