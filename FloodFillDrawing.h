#ifndef FLOODFILLDRAWING_H
#define FLOODFILLDRAWING_H

#include <queue>
#include <utility>
#include "Drawing.h"

class FloodFillDrawing : public Drawable {
private:
  int x;
  int y;
  int width;
  int height;
  uint8_t *buffer;
  void colorPoint(FrameBuffer& frameBuffer, std::queue<std::pair<int, int>>& queue, int x, int y, uint32_t color);
  
public:
  FloodFillDrawing(int x, int y, int width, int height, FrameBuffer& frameBuffer, Drawing& drawing, int start_x, int start_y, int r, int g, int b);
  FloodFillDrawing(const FloodFillDrawing& floodFillDrawing);
  Drawable *clone ();
  void draw(FrameBuffer& frameBuffer);
  void draw(FrameBuffer& frameBuffer, uint8_t* buffer, int width, int height);
  void transform(int d_x, int d_y);
};

#endif
