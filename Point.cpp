#include "Point.h"

Point::Point(): x(0), y(0) {
}

Point::Point(float x, float y) : x(x), y(y) {
}

float Point::getX() {
  return x;
}

float Point::getY() {
  return y;
}

void Point::setX(float v) {
  x = v;
}

void Point::setY(float v) {
  y = v;
}

char Point::calculateOutcode(float left, float top, float right, float bottom) {
  char outcode = INSIDE;
  if (x < left) {
    outcode |= LEFT;
  }
  else if (x > right) {
    outcode |= RIGHT;
  }
  if (y < top) {
    outcode |= TOP;
  }
  else if (y > bottom) {
    outcode |= BOTTOM;
  }
  return outcode;
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

bool Point::operator<(const Point& other) const {
  return (x < other.x) | (x == other.x && y < other.y);
}