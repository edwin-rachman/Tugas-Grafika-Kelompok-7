#ifndef POINT_H
#define POINT_H

#include <cmath>
#include "Drawable.h"

class Point : public Drawable {
private:
  float x;
  float y;
  static const char INSIDE = 0;
  static const char LEFT = 1;
  static const char RIGHT = 2;
  static const char TOP = 4;
  static const char BOTTOM = 8;
  
public:
  Point(float x, float y);
  float getX();
  float getY();
  
  void draw (FrameBuffer& frameBuffer);
  void clippedDraw(FrameBuffer& frameBuffer, float left, float top, float right, float bottom);
  char calculateOutcode(float left, float top, float right, float bottom);
  void translate (float translate_x, float translate_y);
  void scale (float scale_x, float scale_y, float origin_x, float origin_y);
  void rotate (float angle, float origin_x, float origin_y);
  Drawable *clone();
};

#endif
