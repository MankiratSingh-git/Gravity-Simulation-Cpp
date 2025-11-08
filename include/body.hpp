#pragma once
#include "vec2.hpp"
#include <string>

struct Body{
  std::string name;
  double mass;
  Vec2 pos;
  Vec2 posPrev;
  Vec2 velPrev;
  Vec2 vel;
  Vec2 acc;

  Body(std::string name_, double mass_ = 1, Vec2 pos_ = Vec2(0,0), Vec2 vel_ = Vec2(0,0), Vec2 acc_ = Vec2(0,0)){
    name = name_;
    if(mass_ > 0) mass = mass_;
    else mass = 1;
    pos = pos_;
    posPrev = pos;
    vel = vel_;
    velPrev = vel;
    acc = acc_;
  }

  void applyForce(const Vec2& F){
    acc.x += F.x/mass;
    acc.y += F.y/mass;
  }

  void resetAcc(){
    acc = Vec2(0,0);
  }

  void update(double dt){
    vel.x = velPrev.x + acc.x*dt;
    vel.y = velPrev.y + acc.y*dt;

    pos.x = posPrev.x + velPrev.x*dt + 0.5*acc.x*dt*dt;
    pos.y = posPrev.y + velPrev.y*dt + 0.5*acc.y*dt*dt;

    velPrev = vel;
    posPrev = pos;
  }
};