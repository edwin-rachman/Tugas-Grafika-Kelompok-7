#include "FloodFillDrawing.h"

void FloodFillDrawing::colorPoint(FrameBuffer& frameBuffer, std::queue<Point *>& queue, int x, int y, uint32_t color) {
  int width = buffer_br.getX() - buffer_tl.getX() + 1;
  int height = buffer_br.getY() - buffer_tl.getY() + 1;
  
  if (x >= 0 && x < width && y >= 0 && y < height && frameBuffer.getPixel(buffer, width, height, x, y) != color) {
    frameBuffer.setPixel(buffer, width, height, x, y, color);
    queue.push(new Point(x, y));
  }
}

FloodFillDrawing::FloodFillDrawing(float x, float y, float buffer_l, float buffer_t, float buffer_r, float buffer_b, Drawing& drawing, uint8_t r, uint8_t g, uint8_t b) 
  : origin(x, y), buffer_tl(buffer_l, buffer_t), buffer_br(buffer_r, buffer_b), drawing(drawing), r(r), g(g), b(b) {
  /*
  
  uint32_t color = frameBuffer.getColor(r, g, b);
  std::queue<std::pair<int, int>> queue;*/
}

FloodFillDrawing::FloodFillDrawing(const FloodFillDrawing& floodFillDrawing) : origin(origin), buffer_tl(buffer_tl), buffer_br(buffer_br), drawing(drawing) {
}

Drawable *FloodFillDrawing::clone () {
  return new FloodFillDrawing(*this);
}

void FloodFillDrawing::draw(FrameBuffer& frameBuffer) {
  int width = buffer_br.getX() - buffer_tl.getX() + 1;
  int height = buffer_br.getY() - buffer_tl.getY() + 1;
  uint32_t color = frameBuffer.getColor(r, g, b);
  
  buffer = (uint8_t *) mmap(0, width * height * sizeof(uint32_t) , PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, (off_t) 0);
  drawing.draw(frameBuffer, buffer, width, height);
  
  /*std::queue<Point *> queue;
  colorPoint(frameBuffer, queue, origin.getX(), origin.getY(), color);
  
  while (!queue.empty()) {
    Point *point = queue.front();
    
    colorPoint(frameBuffer, queue, point->getX() - 1, point->getY(), color);
    colorPoint(frameBuffer, queue, point->getX() + 1, point->getY(), color);
    colorPoint(frameBuffer, queue, point->getX(), point->getY() - 1, color);
    colorPoint(frameBuffer, queue, point->getX(), point->getY() + 1, color);
    
    delete point;
    queue.pop();
  }*/
  
  for (int buffer_y = 0; buffer_y < height; ++buffer_y) {
    for (int buffer_x = 0; buffer_x < width; ++buffer_x) {
      frameBuffer.setPixel(buffer_tl.getX() + buffer_x, buffer_tl.getY() + buffer_y, frameBuffer.getPixel(buffer, width, height, buffer_x, buffer_y));
    }
  }
}

void FloodFillDrawing::draw(FrameBuffer& frameBuffer, uint8_t* buffer, int width, int height) {
}

void FloodFillDrawing::translate(float d_x, float d_y) {
  drawing.translate(d_x, d_y);
  origin.translate(d_x, d_y);
  buffer_tl.translate(d_x, d_y);
  buffer_br.translate(d_x, d_y);
}

void FloodFillDrawing::scale (float scale_x, float scale_y, float origin_x, float origin_y) {
  drawing.scale(scale_x, scale_y, origin_x, origin_y);
  origin.scale(scale_x, scale_y, origin_x, origin_y);
  buffer_tl.scale(scale_x, scale_y, origin_x, origin_y);
  buffer_br.scale(scale_x, scale_y, origin_x, origin_y);
}

void FloodFillDrawing::rotate (float angle, float origin_x, float origin_y) {
  drawing.rotate(angle, origin_x, origin_y);
  origin.rotate(angle, origin_x, origin_y);
  buffer_tl.rotate(angle, origin_x, origin_y);
  buffer_br.rotate(angle, origin_x, origin_y);
}
