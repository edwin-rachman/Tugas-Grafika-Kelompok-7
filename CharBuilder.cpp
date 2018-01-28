#include "CharBuilder.h"
#include "Line.h"
#include <iostream>
#include <fstream>

Drawing * BuildChar(int x, int y, const char * filename, int width, int height, u_int8_t r, u_int8_t g, u_int8_t b) {
    Drawing * drawing = new Drawing(x, y);
    std::ifstream stream(filename);
    int count;
    stream >> count;
    for (int i = 0; i < count; i++) {
        float x1, y1, x2, y2;
        stream >> x1 >> y1 >> x2 >> y2;
        drawing->add(new Line((int)(x1 * width), (int)(y1 * height), (int)(x2 * width), (int)(y2 * height), r, g, b));
    }
    return drawing;
}