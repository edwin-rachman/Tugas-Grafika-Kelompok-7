#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "FrameBuffer.h"

class Drawable {
public:
  virtual void draw(FrameBuffer& frameBuffer) = 0;
  virtual void transform(int d_x, int d_y) = 0;
};

#endif
