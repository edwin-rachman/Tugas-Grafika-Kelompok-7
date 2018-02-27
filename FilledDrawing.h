#ifndef FILLEDDRAWING_H
#define FILLEDDRAWING_H

#include "Drawable.h"
#include "Drawing.h"

class FilledDrawing : public Drawing {
private:
  uint8_t fill_r;
  uint8_t fill_g;
  uint8_t fill_b;
public:
  FilledDrawing(float x, float y, uint8_t r, uint8_t g, uint8_t b);
  FilledDrawing(const FilledDrawing& drawing);
  FilledDrawing *clone ();
  void draw (FrameBuffer& frameBuffer);
  void clippedDraw(FrameBuffer& frameBuffer, float left, float top, float right, float bottom);
};

#endif
