#ifndef POINT_H
#define POINT_H

#include <cmath>
#include "Drawable.h"

class Point : public Drawable {
private:
  float x;
  float y;
  
public:
  Point(float x, float y);
  float getX();
  float getY();
  
  void draw (FrameBuffer& frameBuffer);
  void draw (FrameBuffer& frameBuffer, uint8_t *buffer, int width, int height);
  void translate (float d_x, float d_y);
  void scale (float s_x, float s_y);
  void rotate (float radian);
  Drawable *clone();
};

#endif
