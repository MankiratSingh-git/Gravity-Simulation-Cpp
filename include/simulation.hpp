#include<vector>
#include"vec2.hpp"
#include"body.hpp"
#include<cmath>

struct Simulation{
  std::vector<Body> bodies;
  double G = 1;
  double time = 0;
  int scale = 1000;
  double s = 1e-4 * scale;

  void step(double dt){

    for(Body& body : bodies){
      body.resetAcc();
    }

    for(int i = 0 ; i < bodies.size() ; ++i){
      for(int j = i+1 ; j < bodies.size() ; ++j){
        if(i==j) continue;
        Vec2 distVec = bodies[i].pos - bodies[j].pos;
        double dist = distVec.length();
        Vec2 unitDist = distVec / dist;
        if(dist < s) continue;
        double force = G*(bodies[i].mass)*(bodies[j].mass) / std::pow((dist*dist + s*s), 1.5);
        Vec2 forceVec = unitDist * force;
        bodies[i].applyForce(forceVec);
        bodies[j].applyForce(-forceVec);
      }
    }

    for(Body& body : bodies){
      body.update(dt);
    }
  }
};