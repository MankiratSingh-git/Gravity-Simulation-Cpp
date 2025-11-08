#pragma once
#include<vector>
#include"body.hpp"

struct Simulation{
  std::vector<Body> bodies;
  double G;
  double time = 0;
  int scale;
  double s;

  Simulation(double G_ = 1.0, int scale_ = 1000): G(G_), scale(scale_) {
    s = 1e-4 * scale;
  }

  void addBody(Body body){
    bodies.push_back(body);
    for(int i = 0 ; i < bodies.size() ; ++i){
      for(int j = i+1 ; j < bodies.size() ; ++j){
        Vec2 distVec = bodies[j].pos - bodies[i].pos;
        double dist = distVec.length();
        Vec2 unitDist = distVec / dist; 
        double force = G*(bodies[i].mass)*(bodies[j].mass) / (dist*dist + s*s);
        Vec2 forceVec = unitDist * force;
        bodies[i].applyForce(forceVec);
        bodies[j].applyForce(-forceVec);
      }
    }

    for(Body& b : bodies){
      b.accPrev = b.acc;
    }
  
  }

  void clear(){
    time = 0;
    while(!bodies.empty()){
      bodies.pop_back();
    }
  }

  const std::vector<Body>& getBodies() const {
    return bodies;
  }

  double getEnergy() const {
    double kinetic = 0;
    double potential = 0;

    for(Body body : bodies){
      kinetic += 0.5*body.mass*body.vel.lengthSquared();
    }

    for(int i = 0 ; i < bodies.size() ; ++i){
      for(int j = i+1 ; j < bodies.size() ; j++){
        potential -= G*bodies[i].mass*bodies[j].mass / sqrt((bodies[i].pos - bodies[j].pos).lengthSquared() + s*s);
      }
    }

    double totalEnergy = potential + kinetic;
    return totalEnergy;
  }

  void step(double dt){

    for(Body& body : bodies){
      body.accPrev = body.acc;
      body.pos = body.pos + (body.vel * dt + 0.5 * body.acc * dt * dt);
    }

    for(Body& body : bodies){
      body.resetAcc();
    }

    for(int i = 0 ; i < bodies.size() ; ++i){
      for(int j = i+1 ; j < bodies.size() ; ++j){
        Vec2 distVec = bodies[j].pos - bodies[i].pos;
        double dist = distVec.length();
        Vec2 unitDist = distVec / dist; 
        double force = G*(bodies[i].mass)*(bodies[j].mass) / (dist*dist + s*s);
        Vec2 forceVec = unitDist * force;
        bodies[i].applyForce(forceVec);
        bodies[j].applyForce(-forceVec);
      }
    }

    for(Body& body : bodies){
      body.vel = body.vel + (0.5 * (body.accPrev + body.acc) * dt);
    }
    time += dt;
  }
};