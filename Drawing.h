#ifndef DRAWING_H
#define DRAWING_H

#include <algorithm>
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
  void remove (Drawable *drawable);
  void draw (FrameBuffer& frameBuffer);
  void draw (FrameBuffer& frameBuffer, uint8_t *buffer, int width, int height);
  void translate (float translate_x, float translate_y);
  void scale (float scale_x, float scale_y, float origin_x, float origin_y);
  void rotate (float angle, float origin_x, float origin_y);
  Point getOrigin ();
  //void floodFill (FrameBuffer& frameBuffer, int width, int height, int x, int y, int r, int g, int b);
};

#endif
