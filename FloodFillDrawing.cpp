#include "FloodFillDrawing.h"

void FloodFillDrawing::colorPoint(FrameBuffer& frameBuffer, std::queue<std::pair<int, int>>& queue, int x, int y, uint32_t color) {
  if (x >= 0 && x < width && y >= 0 && y < height && frameBuffer.getPixel(buffer, width, height, x, y) != color) {
    frameBuffer.setPixel(buffer, width, height, x, y, color);
    queue.push(std::make_pair(x, y));
  }
}

FloodFillDrawing::FloodFillDrawing(int x, int y, int width, int height, FrameBuffer& frameBuffer, Drawing& drawing, int start_x, int start_y, int r, int g, int b) 
  : x(x), y(y), width(width), height(height) {
  buffer = (uint8_t *) mmap(0, width * height * sizeof(uint32_t) , PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, (off_t) 0);
  drawing.draw(frameBuffer, buffer, width, height);
  
  uint32_t color = frameBuffer.getColor(r, g, b);
  std::queue<std::pair<int, int>> queue;
  colorPoint(frameBuffer, queue, start_x, start_y, color);
  
  while (!queue.empty()) {
    auto point = queue.front();
    
    colorPoint(frameBuffer, queue, point.first - 1, point.second, color);
    colorPoint(frameBuffer, queue, point.first + 1, point.second, color);
    colorPoint(frameBuffer, queue, point.first, point.second - 1, color);
    colorPoint(frameBuffer, queue, point.first, point.second + 1, color);
    
    queue.pop();
  }
}

FloodFillDrawing::FloodFillDrawing(const FloodFillDrawing& floodFillDrawing) {
}

Drawable *FloodFillDrawing::clone () {
  return new FloodFillDrawing(*this);
}

void FloodFillDrawing::draw(FrameBuffer& frameBuffer) {
  for (int buffer_y = 0; buffer_y < height; ++buffer_y) {
    for (int buffer_x = 0; buffer_x < width; ++buffer_x) {
      frameBuffer.setPixel(x + buffer_x, y + buffer_y, frameBuffer.getPixel(buffer, width, height, buffer_x, buffer_y));
    }
  }
}

void FloodFillDrawing::draw(FrameBuffer& frameBuffer, uint8_t* buffer, int width, int height) {
}

void FloodFillDrawing::transform(int d_x, int d_y) {
  x += d_x;
  y += d_y;
}

