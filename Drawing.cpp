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

void Drawing::remove (Drawable *drawable) {
  drawables.erase(std::remove(drawables.begin(), drawables.end(), drawable), drawables.end());
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

void Drawing::translate (float translate_x, float translate_y) {
  origin.translate(translate_x, translate_y);
  for (auto& drawable : drawables) {
    drawable->translate(translate_x, translate_y);
  }
}

void Drawing::scale (float scale_x, float scale_y, float origin_x, float origin_y) {
  origin.scale(scale_x, scale_y, origin_x, origin_y);
  for (auto& drawable : drawables) {
    drawable->scale(scale_x, scale_y, origin_x, origin_y);
  }
}

void Drawing::rotate (float angle, float origin_x, float origin_y) {
  origin.rotate(angle, origin_x, origin_y);
  for (auto& drawable : drawables) {
    drawable->rotate(angle, origin_x, origin_y);
  }
}

Point Drawing::getOrigin () {
  return origin;
}
