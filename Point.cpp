#include "Point.h"

Point::Point(float x, float y) : x(x), y(y) {
}

float Point::getX() {
  return x;
}

float Point::getY() {
  return y;
}

void Point::draw (FrameBuffer& frameBuffer) {
}

void Point::draw (FrameBuffer& frameBuffer, uint8_t *buffer, int width, int height) {
}

void Point::translate (float d_x, float d_y) {
  x += d_x;
  y += d_y;
}

void Point::scale (float s_x, float s_y) {
  x *= s_x;
  y *= s_y;
}

void Point::rotate (float radian) {
  float temp_x = x;
  float temp_y = y;
  x = temp_x * std::cos(radian) - temp_y * std::sin(radian);
  y = temp_x * std::sin(radian) + temp_y * std::cos(radian);
}

Drawable *Point::clone() {
  return new Point(*this);
}
