#pragma once
#include "vec2.hpp"
#include <string>

struct Body{
  std::string name;
  double mass;
  Vec2 pos;
  Vec2 vel;
  Vec2 acc;

  Body(std::string name_, double mass_ = 0, Vec2 pos_ = Vec2(0,0), Vec2 vel_ = Vec2(0,0), Vec2 acc_ = Vec2(0,0)){
    name = name_;
    if(mass_ > 0) mass = mass_;
    pos = pos_;
    vel = vel_;
    acc = acc_;
  }

  void applyForce(const Vec2& F){
    acc.x = F.x/mass;
    acc.y = F.y/mass;
  }

  void resetAcc(){
    acc = Vec2(0,0);
  }

  void update(double dt){
    vel.x = vel.x + acc.x*dt;
    vel.y = vel.y + acc.y*dt;
  }
};