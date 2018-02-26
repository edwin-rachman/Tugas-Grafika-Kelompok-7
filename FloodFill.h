#ifndef FLOODFILL_H
#define FLOODFILL_H

#include "FrameBuffer.h"

void FloodFill(FrameBuffer& frameBuffer, int x, int y, uint8_t r, uint8_t g, uint8_t b);

void FloodFill(FrameBuffer& frameBuffer, int lt_x, int lt_y, int br_x, int br_y, int x, int y, uint8_t r, uint8_t g, uint8_t b);

#endif
