#ifndef LINE_H
#define LINE_H

#include <cmath>
#include "Drawable.h"
#include "FrameBuffer.h"

class Line : public Drawable {
private:
	int x_0;
	int y_0;
	int x_1;
	int y_1;
	uint8_t r;
	uint8_t g;
	uint8_t b;
	
public:
	Line(int x_0, int y_0, int x_1, int y_1, uint8_t r, uint8_t g, uint8_t b);
  Drawable *clone();
	void draw(FrameBuffer& frameBuffer);
	void transform(int d_x, int d_y);
};

#endif
