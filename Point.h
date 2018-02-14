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
  void translate (float translate_x, float translate_y);
  void scale (float scale_x, float scale_y, float origin_x, float origin_y);
  void rotate (float angle, float origin_x, float origin_y);
  Drawable *clone();
};

#endif
