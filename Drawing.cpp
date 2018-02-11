#include "Drawing.h"

Drawing::Drawing (float x, float y) : origin(x, y) {
}

Drawing::Drawing (const Drawing& drawing) : origin(drawing.origin) {
  for (auto& drawable : drawing.drawables) {
    drawables.push_back(drawable->clone());
  }
}

Drawable *Drawing::clone () {
  return new Drawing(*this);
}

void Drawing::add (Drawable *drawable) {
  drawable->translate(origin.getX(), origin.getY());
  drawables.push_back(drawable);
}

void Drawing::draw (FrameBuffer& frameBuffer) {
  for (auto& drawable : drawables) {
    drawable->draw(frameBuffer);
  }
}

void Drawing::draw (FrameBuffer& frameBuffer, uint8_t *buffer, int width, int height) {
  for (auto& drawable : drawables) {
    drawable->draw(frameBuffer, buffer, width, height);
  }
}

void Drawing::translate (float d_x, float d_y) {
  origin.translate(d_x, d_y);
  for (auto& drawable : drawables) {
    drawable->translate(d_x, d_y);
  }
}

void Drawing::scale (float s_x, float s_y) {
  origin.scale(s_x, s_y);
  for (auto& drawable : drawables) {
    drawable->scale(s_x, s_y);
  }
}

void Drawing::rotate (float radian) {
  origin.rotate(radian);
  for (auto& drawable : drawables) {
    drawable->rotate(radian);
  }
}
