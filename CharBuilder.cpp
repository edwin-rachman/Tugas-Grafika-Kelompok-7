#include "CharBuilder.h"
#include "Line.h"
#include "Drawing.h"
#include "FilledDrawing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Drawing * BuildChar(int x, int y, string filename, int width, int height, u_int8_t r, u_int8_t g, u_int8_t b) {
    Drawing * drawing = new Drawing(x, y);
    ifstream stream(filename, ifstream::in);
    int count;
    stream >> count;
    for (int i = 0; i < count; i++) {
        float x1, y1, x2, y2;
        stream >> x1 >> y1 >> x2 >> y2;
        drawing->add(new Line((int)(x1 * width), (int)(y1 * height), (int)(x2 * width), (int)(y2 * height), r, g, b));
    }
    stream.close();
    return drawing;
}

FilledDrawing * BuildCharFilled(int x, int y, string filename, int width, int height, u_int8_t r, u_int8_t g, u_int8_t b) {
    FilledDrawing * drawing = new FilledDrawing(x, y, r, g, b);
    ifstream stream(filename, ifstream::in);
    int count;
    stream >> count;
    for (int i = 0; i < count; i++) {
        float x1, y1, x2, y2;
        stream >> x1 >> y1 >> x2 >> y2;
        drawing->add(new Line((int)(x1 * width), (int)(y1 * height), (int)(x2 * width), (int)(y2 * height), r, g, b));
    }
    stream.close();
    return drawing;
}