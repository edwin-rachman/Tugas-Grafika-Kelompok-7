#ifndef SHAPEBUILDER_H
#define SHAPEBUILDER_H

#include "Drawing.h"
#include "FilledDrawing.h"
#include "Line.h"

Drawing * createBox(float min_x, float min_y, float max_x, float max_y, uint8_t r, uint8_t g, uint8_t b);
Drawing * createFilledBox(float min_x, float min_y, float max_x, float max_y, uint8_t r, uint8_t g, uint8_t b);

#endif