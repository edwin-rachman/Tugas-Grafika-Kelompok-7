#include "Drawing.h"

Drawing::Drawing (int x, int y) : x(x), y(y) {
}

Drawing::~Drawing () {
}


void Drawing::add (Drawable *drawable) {
  drawable->transform(x, y);
  drawables.push_back(drawable);
}

void Drawing::draw (FrameBuffer& frameBuffer) {
  for (auto& drawable : drawables) {
    drawable->draw(frameBuffer);
  }
}

void Drawing::transform (int d_x, int d_y) {
  x += d_x;
  y += d_y;
  for (auto& drawable : drawables) {
    drawable->transform(d_x, d_y);
  }
}

int Drawing::getX () {
  return x;
}

int Drawing::getY () {
  return y;
}
