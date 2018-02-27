#ifndef POINT_H
#define POINT_H

#include <cmath>

class Point {
private:
  float x;
  float y;
  static const char INSIDE = 0;
  static const char LEFT = 1;
  static const char RIGHT = 2;
  static const char TOP = 4;
  static const char BOTTOM = 8;
  
public:
  Point();
  Point(float x, float y);
  float getX();
  float getY();
  void setX(float v);
  void setY(float v);
  
  char calculateOutcode(float left, float top, float right, float bottom);
  void translate (float translate_x, float translate_y);
  void scale (float scale_x, float scale_y, float origin_x, float origin_y);
  void rotate (float angle, float origin_x, float origin_y);
  
  bool operator<(const Point& other) const;
};

#endif
