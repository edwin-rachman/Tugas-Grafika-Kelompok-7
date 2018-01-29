#include "Line.h"

Line::Line(int x_0, int y_0, int x_1, int y_1, uint8_t r, uint8_t g, uint8_t b)
 : x_0(x_0), y_0(y_0), x_1(x_1), y_1(y_1), r(r), g(g), b(b) {
}

Drawable *Line::clone () {
  return new Line(*this);
}

void Line::draw(FrameBuffer& frameBuffer) {
  int d_x = x_1 - x_0;
  int d_y = y_1 - y_0;
  int d_x_abs = std::abs(d_x);
  int d_y_abs = std::abs(d_y);
  int sign_d_x = d_x > 0 ? 1 : -1;
  int sign_d_y = d_y > 0 ? 1 : -1;
  int x = d_y_abs >> 1;
  int y = d_x_abs >> 1;
  int p_x = x_0;
  int p_y = y_0;
  
  frameBuffer.setPixel(p_x, p_y, r, g, b);
  if (d_x_abs >= d_y_abs) {
    for (int i = 0; i < d_x_abs; ++i) {
      y += d_y_abs;
      if (y >= d_x_abs) {
        y -= d_x_abs;
        p_y += sign_d_y;
      }
      p_x += sign_d_x;
      frameBuffer.setPixel(p_x, p_y, r, g, b);
    }
  }
  else {
    for (int i = 0; i < d_y_abs; ++i) {
      x += d_x_abs;
      if (x >= d_y_abs) {
        x -= d_y_abs;
        p_x += sign_d_x;
      }
      p_y += sign_d_y;
      frameBuffer.setPixel(p_x, p_y, r, g, b);
    }
  }
}



void Line::transform(int d_x, int d_y) {
  x_0 += d_x;
  y_0 += d_y;
  x_1 += d_x;
  y_1 += d_y;
}
