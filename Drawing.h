#ifndef DRAWING_H
#define DRAWING_H

#include <cstdint>
#include <cmath>
#include <vector>
#include "Point.h"

class Drawing : public Drawable {
private:
  Point origin;
  std::vector<Drawable *> drawables;

public:
  Drawing (float x, float y);
  Drawing (const Drawing& drawing);
  Drawable *clone ();
  void add (Drawable *drawable);
  void draw (FrameBuffer& frameBuffer);
  void draw (FrameBuffer& frameBuffer, uint8_t *buffer, int width, int height);
  void translate (float d_x, float d_y);
  void scale (float s_x, float s_y);
  void rotate (float radian);
  //void floodFill (FrameBuffer& frameBuffer, int width, int height, int x, int y, int r, int g, int b);
};

#endif
