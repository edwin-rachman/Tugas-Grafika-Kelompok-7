#include "ShapeBuilder.h"

Drawing * createBox(float min_x, float min_y, float max_x, float max_y, uint8_t r, uint8_t g, uint8_t b) {
    Drawing * newDrawing = new FilledDrawing(min_x, min_y, r, g, b);
    // Top Line.
    newDrawing->add(new Line(min_x, min_y, max_x, min_y, r, g, b));
    // Right Line.
    newDrawing->add(new Line(max_x, min_y, max_x, max_y, r, g, b));
    // Bottom Line.
    newDrawing->add(new Line(min_x, max_y, max_x, max_y, r, g, b));
    // Left Line.
    newDrawing->add(new Line(min_x, min_y, min_x, max_y, r, g, b));
    return newDrawing;
}

Drawing * createFilledBox(float min_x, float min_y, float max_x, float max_y, uint8_t r, uint8_t g, uint8_t b) {
    FilledDrawing * newDrawing = new FilledDrawing(min_x, min_y, r, g, b);
    // Top Line.
    newDrawing->add(new Line(min_x, min_y, max_x, min_y, r, g, b));
    // Right Line.
    newDrawing->add(new Line(max_x, min_y, max_x, max_y, r, g, b));
    // Bottom Line.
    newDrawing->add(new Line(min_x, max_y, max_x, max_y, r, g, b));
    // Left Line.
    newDrawing->add(new Line(min_x, min_y, min_x, max_y, r, g, b));
    return newDrawing;
}