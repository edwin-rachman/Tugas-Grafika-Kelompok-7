#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "FrameBuffer.h"

class Drawable {
public:
  virtual void draw(FrameBuffer& frameBuffer, uint8_t* buffer, int width, int height) = 0;
  virtual void draw(FrameBuffer& frameBuffer) = 0;
  virtual void translate(float d_x, float d_y) = 0;
  virtual void scale(float s_x, float s_y) = 0;
  virtual void rotate(float radian) = 0;
  virtual Drawable *clone() = 0;
};

#endif
