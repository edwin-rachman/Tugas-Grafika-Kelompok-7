#ifndef FLOODFILLDRAWING_H
#define FLOODFILLDRAWING_H

#include <queue>
#include <utility>
#include "Drawing.h"

class FloodFillDrawing : public Drawable {
private:
  Point origin;
  Point buffer_tl;
  Point buffer_br;
  Drawing& drawing;
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t *buffer;
  void colorPoint(FrameBuffer& frameBuffer, std::queue<Point *>& queue, int x, int y, uint32_t color);
  
public:
  FloodFillDrawing(float x, float y, float buffer_l, float buffer_t, float buffer_r, float buffer_b, Drawing& drawing, uint8_t r, uint8_t g, uint8_t b);
  FloodFillDrawing(const FloodFillDrawing& floodFillDrawing);
  Drawable *clone ();
  void draw(FrameBuffer& frameBuffer);
  void draw(FrameBuffer& frameBuffer, uint8_t *buffer, int width, int height);
  void translate(float d_x, float d_y);
  void scale (float scale_x, float scale_y, float origin_x, float origin_y);
  void rotate (float angle, float origin_x, float origin_y);
};

#endif
