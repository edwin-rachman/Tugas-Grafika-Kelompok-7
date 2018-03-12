#ifndef FILLEDDRAWING_H
#define FILLEDDRAWING_H

#include "Drawable.h"
#include "Drawing.h"
#include "Line.h"
#include "IntersectionMap.h"

class FilledDrawing : public Drawing {
private:
  uint8_t fill_r;
  uint8_t fill_g;
  uint8_t fill_b;
  std::vector<Line *> lines;

  IntersectionMap intersectionMap;

public:
  FilledDrawing(float x, float y, uint8_t r, uint8_t g, uint8_t b);
  FilledDrawing(const FilledDrawing& drawing);
  Drawable *clone ();
  void add (Drawable *drawable);
  void remove (Drawable *drawable);
  void draw (FrameBuffer& frameBuffer);
  void clippedDraw(FrameBuffer& frameBuffer, float left, float top, float right, float bottom);
  void translate (float translate_x, float translate_y);
  void scale (float scale_x, float scale_y, float origin_x, float origin_y);
  void rotate (float angle, float origin_x, float origin_y);
  void setColor(uint8_t r, uint8_t g, uint8_t b);
};

#endif
