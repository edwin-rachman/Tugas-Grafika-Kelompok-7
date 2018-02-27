#ifndef CHARBUILDER_H
#define CHARBUILDER_H

#include "Drawing.h"
#include "FilledDrawing.h"
#include <string>
using namespace std;

Drawing * BuildChar(int, int, string filename, int width, int height, u_int8_t, u_int8_t, u_int8_t);
FilledDrawing * BuildCharFilled(int, int, string filename, int width, int height, u_int8_t, u_int8_t, u_int8_t);

#endif