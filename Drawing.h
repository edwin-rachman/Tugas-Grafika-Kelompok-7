#ifndef DRAWING_H
#define DRAWING_H

#include <algorithm>
#include <cstdint>
#include <cmath>
#include <vector>
#include "Drawable.h"
#include "Point.h"

class Drawing : public Drawable {
protected:
  Point origin;
  std::vector<Drawable *> drawables;
  uint32_t color;
  Point _minBoundary;
  Point _maxBoundary;
public:
  Drawing (float x, float y);
  Drawing (const Drawing& drawing);
  virtual Drawable *clone ();
  virtual void add (Drawable *drawable);
  virtual void remove (Drawable *drawable);
  virtual void draw (FrameBuffer& frameBuffer);
  virtual void clippedDraw(FrameBuffer& frameBuffer, float left, float top, float right, float bottom);
  virtual void translate (float translate_x, float translate_y);
  virtual void scale (float scale_x, float scale_y, float origin_x, float origin_y);
  virtual void rotate (float angle, float origin_x, float origin_y);
  virtual void setColor(uint8_t r, uint8_t g, uint8_t b);
  Point minBoundary();
  Point maxBoundary();
  Point getOrigin ();
  //void floodFill (FrameBuffer& frameBuffer, int width, int height, int x, int y, int r, int g, int b);
};

#endif
