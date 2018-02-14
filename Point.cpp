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

void Point::translate (float translate_x, float translate_y) {
  x += translate_x;
  y += translate_y;
}

void Point::scale (float scale_x, float scale_y, float origin_x, float origin_y) {
  translate(-origin_x, -origin_y);
  x *= scale_x;
  y *= scale_y;
  translate(origin_x, origin_y);
}

void Point::rotate (float angle, float origin_x, float origin_y) {
  translate(-origin_x, -origin_y);
  float temp_x = x;
  float temp_y = y;
  x = temp_x * std::cos(angle) - temp_y * std::sin(angle);
  y = temp_x * std::sin(angle) + temp_y * std::cos(angle);
  translate(origin_x, origin_y);
}

Drawable *Point::clone() {
  return new Point(*this);
}
