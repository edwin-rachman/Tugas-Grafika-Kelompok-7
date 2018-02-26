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

public:
	Line(float x_0, float y_0, float x_1, float y_1, uint8_t r, uint8_t g, uint8_t b);
  Drawable *clone();
	void draw(FrameBuffer& frameBuffer);
  void draw(FrameBuffer& frameBuffer, uint8_t *buffer, int width, int height);
	void translate(float d_x, float d_y);
  void scale(float s_x, float s_y);
  void rotate(float radian);
  Point getTop();
  Point getBottom();
  Point getLeft();
  Point getRight();
};

#endif
