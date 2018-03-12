#include "Line.h"

Line::Line(Point p0, Point p1, uint8_t r, uint8_t g, uint8_t b) : p0(p0), p1(p1), r(r), g(g), b(b) {
}

Line::Line(float x_0, float y_0, float x_1, float y_1, uint8_t r, uint8_t g, uint8_t b)
 : p0(x_0, y_0), p1(x_1, y_1), r(r), g(g), b(b) {
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

void Line::clippedDraw(FrameBuffer& frameBuffer, float left, float top, float right, float bottom) {
  Point clippedP0 = p0;
  Point clippedP1 = p1;
  char outcode0 = clippedP0.calculateOutcode(left, top, right, bottom);
  char outcode1 = clippedP1.calculateOutcode(left, top, right, bottom);

  bool accept = false;
  for (;;) {
    if (!(outcode0 | outcode1)) {
      accept = true;
      break;
    }
    else if (outcode0 & outcode1) {
      break;
    }
    else {
      char outcode = outcode0 ? outcode0 : outcode1;
      float x, y;
      if (outcode & TOP) {
        x = getXIntersection(top);
        y = top;
      }
      else if (outcode & BOTTOM) {
        x = getXIntersection(bottom);
        y = bottom;
      }
      else if (outcode & LEFT) {
        x = left;
        y = getYIntersection(left);
      }
      else if (outcode & RIGHT) {
        x = right;
        y = getYIntersection(right);
      }
      if (outcode == outcode0) {
        clippedP0 = Point(x, y);
        outcode0 = clippedP0.calculateOutcode(left, top, right, bottom);
      }
      else {
        clippedP1 = Point(x, y);
        outcode1 = clippedP1.calculateOutcode(left, top, right, bottom);
      }
    }
  }

  if (accept) {
    int d_x = clippedP1.getX() - clippedP0.getX();
    int d_y = clippedP1.getY() - clippedP0.getY();
    int d_x_abs = std::abs(d_x);
    int d_y_abs = std::abs(d_y);
    int sign_d_x = d_x > 0 ? 1 : -1;
    int sign_d_y = d_y > 0 ? 1 : -1;
    int x = d_y_abs >> 1;
    int y = d_x_abs >> 1;
    int p_x = clippedP0.getX();
    int p_y = clippedP0.getY();

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
}


void Line::translate(float translate_x, float translate_y) {
  p0.translate(translate_x, translate_y);
  p1.translate(translate_x, translate_y);
}

void Line::scale(float scale_x, float scale_y, float origin_x, float origin_y) {
  p0.scale(scale_x, scale_y, origin_x, origin_y);
  p1.scale(scale_x, scale_y, origin_x, origin_y);
}

void Line::rotate(float angle, float origin_x, float origin_y) {
  p0.rotate(angle, origin_x, origin_y);
  p1.rotate(angle, origin_x, origin_y);
}

void Line::setColor(uint8_t r, uint8_t g, uint8_t b) {
  this->r = r;
  this->g = g;
  this->b = b;
}

float Line::getXIntersection(float y) {
  return p0.getX() + (p1.getX() - p0.getX()) * ((y - p0.getY()) / (p1.getY() - p0.getY()));
}

float Line::getYIntersection(float x) {
  return p0.getY() + (p1.getY() - p0.getY()) * ((x - p0.getX()) / (p1.getX() - p0.getX()));
}

bool Line::isWithinXRange(float x) {
  if (p0.getX() > p1.getX()) {
    return x >= p0.getX() && x <= p1.getX();
  }
  else {
    return x >= p1.getX() && x <= p0.getX();
  }
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

Point Line::minBoundary() {
  Point p;
  if (p0.getX() < p1.getX()) {
    p.setX(p0.getX());
  } else {
    p.setX(p1.getX());
  }
  if (p0.getY() < p1.getY()) {
    p.setY(p0.getY());
  } else {
    p.setY(p1.getY());
  }
  return p;
}

Point Line::maxBoundary() {
  Point p;
  if (p0.getX() > p1.getX()) {
    p.setX(p0.getX());
  } else {
    p.setX(p1.getX());
  }
  if (p0.getY() > p1.getY()) {
    p.setY(p0.getY());
  } else {
    p.setY(p1.getY());
  }
  return p;
}

Point Line::getPointOrigin() {
  return p0;
}
Point Line::getPointDestination() {
  return p1;
}
