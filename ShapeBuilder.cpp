#include "ShapeBuilder.h"
#include <math.h>
using namespace std;

const float PI = acos(-1);

Drawing * createBox(float min_x, float min_y, float max_x, float max_y, uint8_t r, uint8_t g, uint8_t b) {
    Drawing * newDrawing = new Drawing((min_x + max_x) / 2, (min_y + max_y) / 2);
    float width = max_x - min_x;
    float height = max_y - min_y;
    float left = -width/2;
    float right = width/2;
    float top = -height/2;
    float bottom = height/2;
    // Top Line.
    newDrawing->add(new Line(left, top, right, top, r, g, b));
    // Right Line.
    newDrawing->add(new Line(right, top, right, bottom, r, g, b));
    // Bottom Line.
    newDrawing->add(new Line(left, bottom, right, bottom, r, g, b));
    // Left Line.
    newDrawing->add(new Line(left, top, left, bottom, r, g, b));
    return newDrawing;
}

Drawing * createFilledBox(float min_x, float min_y, float max_x, float max_y, uint8_t r, uint8_t g, uint8_t b) {
    Drawing * newDrawing = new FilledDrawing((min_x + max_x) / 2, (min_y + max_y) / 2, r, g, b);
    float width = max_x - min_x;
    float height = max_y - min_y;
    float left = -width/2;
    float right = width/2;
    float top = -height/2;
    float bottom = height/2;
    // Top Line.
    newDrawing->add(new Line(left, top, right, top, r, g, b));
    // Right Line.
    newDrawing->add(new Line(right, top, right, bottom, r, g, b));
    // Bottom Line.
    newDrawing->add(new Line(left, bottom, right, bottom, r, g, b));
    // Left Line.
    newDrawing->add(new Line(left, top, left, bottom, r, g, b));
    return newDrawing;
}

Drawing * createCircle(float x, float y, float radius, uint8_t r, uint8_t g, uint8_t b, int segments) {
    Drawing * newDrawing = new Drawing(x, y);
    float interval = 2 * PI / segments;
    float angle = 0;
    for (int i = 0; i < segments; i++) {
        newDrawing->add(new Line((radius * cos(angle)), (radius * sin(angle)), (radius * cos(angle + interval)), (radius * sin(angle + interval)), r, g, b));
        angle += interval;
    }
    return newDrawing;
}

Drawing * createFilledCircle(float x, float y, float radius, uint8_t r, uint8_t g, uint8_t b, int segments) {
    Drawing * newDrawing = new FilledDrawing(x, y, r, g, b);
    float interval = 2 * PI / segments;
    float angle = 0;
    for (int i = 0; i < segments; i++) {
        newDrawing->add(new Line((radius * cos(angle)), (radius * sin(angle)), (radius * cos(angle + interval)), (radius * sin(angle + interval)), r, g, b));
        angle += interval;
    }
    return newDrawing;
}