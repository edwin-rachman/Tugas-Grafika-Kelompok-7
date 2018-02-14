#ifndef LINE_H
#define LINE_H

#include <cmath>
#include "Point.h"

class Line : public Drawable {
private:
  Point origin;
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
	void translate(float translate_x, float translate_y);
  void scale(float scale_x, float scale_y, float origin_x, float origin_y);
  void rotate(float angle, float origin_x, float origin_y);
  Point getTop();
  Point getBottom();
  Point getLeft();
  Point getRight();
};

#endif
