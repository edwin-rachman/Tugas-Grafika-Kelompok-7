#ifndef LINE_H
#define LINE_H

#include <cmath>
#include "Point.h"

class Line : public Drawable {
private:
	Point p0;
	Point p1;
	uint8_t r;
	uint8_t g;
	uint8_t b;
  char calculateOutcode(Point p, float left, float top, float right, float bottom);
  static const char INSIDE = 0;
  static const char LEFT = 1;
  static const char RIGHT = 2;
  static const char TOP = 4;
  static const char BOTTOM = 8;
	
public:
  Line(Point p0, Point p1);
	Line(float x_0, float y_0, float x_1, float y_1, uint8_t r, uint8_t g, uint8_t b);
  Drawable *clone();
	void draw(FrameBuffer& frameBuffer);
  void clippedDraw(FrameBuffer& frameBuffer, float left, float top, float right, float bottom);
	void translate(float translate_x, float translate_y);
  void scale(float scale_x, float scale_y, float origin_x, float origin_y);
  void rotate(float angle, float origin_x, float origin_y);
  float getXIntersection(float y);
  float getYIntersection(float x);
  bool isWithinXRange(float x);
  Point getTop();
  Point getBottom();
  Point getLeft();
  Point getRight();
};

#endif
