#include "Drawing.h"

Drawing::Drawing (float x, float y) : origin(x, y) {
}

Drawing::Drawing (const Drawing& drawing) : origin(drawing.origin) {
  for (auto& drawable : drawing.drawables) {
    drawables.push_back(drawable->clone());
    // Recalculate boundary.
	  float min_x = drawable->minBoundary().getX();
	  float min_y = drawable->minBoundary().getY();
	  float max_x = drawable->maxBoundary().getX();
	  float max_y = drawable->maxBoundary().getY();
	  if (min_x < _minBoundary.getX()) {
		_minBoundary.setX(min_x);
	  }
	  if (min_y < _minBoundary.getY()) {
		_minBoundary.setY(min_y);
	  }
	  if (max_x > _maxBoundary.getX()) {
		_maxBoundary.setX(max_x);
	  }
	  if (max_y > _maxBoundary.getY()) {
		_maxBoundary.setY(max_y);
	  };
  }
}

Drawable *Drawing::clone () {
  return new Drawing(*this);
}

void Drawing::add (Drawable *drawable) {
  drawable->translate(origin.getX(), origin.getY());
  drawables.push_back(drawable);
  // Recalculate boundary.
  float min_x = drawable->minBoundary().getX();
  float min_y = drawable->minBoundary().getY();
  float max_x = drawable->maxBoundary().getX();
  float max_y = drawable->maxBoundary().getY();
  if (min_x < _minBoundary.getX()) {
    _minBoundary.setX(min_x);
  }
  if (min_y < _minBoundary.getY()) {
    _minBoundary.setY(min_y);
  }
  if (max_x > _maxBoundary.getX()) {
    _maxBoundary.setX(max_x);
  }
  if (max_y > _maxBoundary.getY()) {
    _maxBoundary.setY(max_y);
  }
}

void Drawing::remove (Drawable *drawable) {
  drawables.erase(std::remove(drawables.begin(), drawables.end(), drawable), drawables.end());
}

void Drawing::draw (FrameBuffer& frameBuffer) {
  for (auto& drawable : drawables) {
    drawable->draw(frameBuffer);
  }
}

void Drawing::clippedDraw(FrameBuffer& frameBuffer, float left, float top, float right, float bottom) {
  for (auto& drawable : drawables) {
    drawable->clippedDraw(frameBuffer, left, top, right, bottom);
  }
}

void Drawing::translate (float translate_x, float translate_y) {
  origin.translate(translate_x, translate_y);
  for (auto& drawable : drawables) {
    drawable->translate(translate_x, translate_y);
  }
  _minBoundary.translate(translate_x, translate_y);
  _maxBoundary.translate(translate_x, translate_y);
}

void Drawing::scale (float scale_x, float scale_y, float origin_x, float origin_y) {
  origin.scale(scale_x, scale_y, origin_x, origin_y);
  for (auto& drawable : drawables) {
    drawable->scale(scale_x, scale_y, origin_x, origin_y);
  }
  _minBoundary.scale(scale_x, scale_y, origin_x, origin_y);
  _maxBoundary.scale(scale_x, scale_y, origin_x, origin_y);
}

void Drawing::rotate (float angle, float origin_x, float origin_y) {
  origin.rotate(angle, origin_x, origin_y);
  for (auto& drawable : drawables) {
    drawable->rotate(angle, origin_x, origin_y);
  }
  _minBoundary.rotate(angle, origin_x, origin_y);
  _maxBoundary.rotate(angle, origin_x, origin_y);
}

Point Drawing::getOrigin () {
  return origin;
}

Point Drawing::minBoundary() {
  return _minBoundary;
}

Point Drawing::maxBoundary() {
  return _maxBoundary;
}
