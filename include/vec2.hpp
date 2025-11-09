#pragma once
#include<cmath>
struct Vec2{

  double x;
  double y;
  Vec2(double x_ = 0, double y_ = 0): x(x_), y(y_){}

  double length() const {
    return  std::sqrt(x*x+y*y);
  }

  double lengthSquared() const {
    return (x * x + y * y);
  }

  Vec2 normalize() const {
    Vec2 vec3;
    double len = this->length();
    if(len > 0){
      vec3.x = x /len;
      vec3.y = y/len;
      return vec3;
    }
    else return Vec2();
  }
};

inline Vec2 operator+(const Vec2& v1, const Vec2& v2){
  Vec2 v3 = Vec2(v1.x + v2.x, v1.y + v2.y);
  return v3;
}

inline Vec2 operator-(const Vec2& v1, const Vec2& v2){
  Vec2 v3 = Vec2(v1.x - v2.x, v1.y - v2.y);
  return v3;
}

inline Vec2 operator*(const Vec2& v, double scalar){
  Vec2 v3 = Vec2(v.x * scalar, v.y * scalar);
  return v3;
}
inline Vec2 operator*(double scalar, const Vec2& v){
  Vec2 v3 = Vec2(v.x * scalar, v.y * scalar);
  return v3;
}

inline Vec2 operator/(const Vec2& v, double scalar){
  Vec2 v3 = Vec2(v.x / scalar, v.y / scalar);
  return v3;
}
inline Vec2 operator/(double scalar, const Vec2& v){
  Vec2 v3 = Vec2(v.x / scalar, v.y / scalar);
  return v3;
}

inline Vec2 operator-(const Vec2& v){
  return Vec2(-v.x, -v.y);
}

inline double dot(const Vec2& v1, const Vec2& v2){
  return (v1.x*v2.x + v1.y*v2.y);
}