#include "Line.h"

Line::Line(float x_0, float y_0, float x_1, float y_1, uint8_t r, uint8_t g, uint8_t b)
 : p0(x_0, y_0), p1(x_1, y_1), r(r), g(g), b(b) {
}

Drawable *Line::clone () {
  return new Line(*this);
}

Drawable *Line::clone () {
  return new Line(*this);
}

void Line::draw(FrameBuffer& frameBuffer) {
  int d_x = p1.getX() - p0.getX();
  int d_y = p1.getY() - p0.getY();
  int d_x_abs = std::abs(d_x);
  int d_y_abs = std::abs(d_y);
  int sign_d_x = d_x > 0 ? 1 : -1;
  int sign_d_y = d_y > 0 ? 1 : -1;
  int x = d_y_abs >> 1;
  int y = d_x_abs >> 1;
  int p_x = p0.getX();
  int p_y = p0.getY();

  frameBuffer.setPixel(p_x, p_y, frameBuffer.getColor(r, g, b));
  if (d_x_abs >= d_y_abs) {
    for (int i = 0; i < d_x_abs; ++i) {
      y += d_y_abs;
      if (y >= d_x_abs) {
        y -= d_x_abs;
        p_y += sign_d_y;
      }
      p_x += sign_d_x;
      frameBuffer.setPixel(p_x, p_y, frameBuffer.getColor(r, g, b));
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
      frameBuffer.setPixel(p_x, p_y, frameBuffer.getColor(r, g, b));
    }
  }
}

void Line::draw(FrameBuffer& frameBuffer, uint8_t *buffer, int width, int height) {
  int d_x = p1.getX() - p0.getX();
  int d_y = p1.getY() - p0.getY();
  int d_x_abs = std::abs(d_x);
  int d_y_abs = std::abs(d_y);
  int sign_d_x = d_x > 0 ? 1 : -1;
  int sign_d_y = d_y > 0 ? 1 : -1;
  int x = d_y_abs >> 1;
  int y = d_x_abs >> 1;
  int p_x = p0.getX();
  int p_y = p0.getY();

  frameBuffer.setPixel(buffer, width, height, p_x, p_y, frameBuffer.getColor(r, g, b));
  if (d_x_abs >= d_y_abs) {
    for (int i = 0; i < d_x_abs; ++i) {
      y += d_y_abs;
      if (y >= d_x_abs) {
        y -= d_x_abs;
        p_y += sign_d_y;
      }
      p_x += sign_d_x;
      frameBuffer.setPixel(buffer, width, height, p_x, p_y, frameBuffer.getColor(r, g, b));
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
      frameBuffer.setPixel(buffer, width, height, p_x, p_y, frameBuffer.getColor(r, g, b));
    }
  }
}


void Line::translate(float d_x, float d_y) {
  p0.translate(d_x, d_y);
  p1.translate(d_x, d_y);
}

void Line::scale(float s_x, float s_y) {
  p0.scale(s_x, s_y);
  p1.scale(s_x, s_y);
}

void Line::rotate(float radian) {
  p0.rotate(radian);
  p1.rotate(radian);
}

Point Line::getTop() {
  return p0.getY() < p1.getY() ? p0 : p1;
}

Point Line::getBottom() {
  return p0.getY() > p1.getY() ? p0 : p1;
}

Point Line::getLeft() {
  return p0.getX() < p1.getX() ? p0 : p1;
}

Point Line::getRight() {
  return p0.getX() > p1.getX() ? p0 : p1;
}
