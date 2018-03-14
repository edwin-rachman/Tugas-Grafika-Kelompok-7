#ifndef SHAPEBUILDER_H
#define SHAPEBUILDER_H

#include "Drawing.h"
#include "FilledDrawing.h"
#include "Line.h"
#include <string>
using namespace std;

Drawing * createBox(float min_x, float min_y, float max_x, float max_y, uint8_t r, uint8_t g, uint8_t b);
Drawing * createFilledBox(float min_x, float min_y, float max_x, float max_y, uint8_t r, uint8_t g, uint8_t b);
Drawing * createCircle(float x, float y, float radius, uint8_t r, uint8_t g, uint8_t b, int segments = 12);
Drawing * createFilledCircle(float x, float y, float radius, uint8_t r, uint8_t g, uint8_t b, int segments = 12);

Drawing * createText(string text, float size, float x, float y, uint8_t r, uint8_t g, uint8_t b);
Drawing * createCharacter(char c, float size, float x, float y, uint8_t r, uint8_t g, uint8_t b);
Drawing * createFilledCharacter(char c, float size, float x, float y, uint8_t r, uint8_t g, uint8_t b);

#endif