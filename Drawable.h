#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "FrameBuffer.h"

class Drawable {
public:
  virtual void draw(FrameBuffer& frameBuffer) = 0;
  virtual void clippedDraw(FrameBuffer& frameBuffer, float left, float top, float right, float bottom) = 0;
  virtual void translate(float translate_x, float translate_y) = 0;
  virtual void scale(float scale_x, float scale_y, float origin_x, float origin_y) = 0;
  virtual void rotate(float angle, float origin_x, float origin_y) = 0;
  virtual Drawable *clone() = 0;
};

#endif
