#include "ShapeBuilder.h"
#include "CharBuilder.h"
#include <math.h>
#include <iostream>
#include <string>
using namespace std;

const float PI = acos(-1);

Drawing * createText(string text, float size, float x, float y, uint8_t r, uint8_t g, uint8_t b) {
    Drawing * root = new Drawing(x, y);
    float offset = 0;
    float r_size = size * 9;
    for (int i = 0; i < text.size(); i++) {
        Drawing * character = createFilledCharacter(text[i], size, offset, 0, r, g, b);
        root->add(character);
        // offset += character->maxBoundary().getX() - character->minBoundary().getX() + size;
        offset += r_size;
    }
    return root;
}

Drawing * createCharacter(char c, float size, float x, float y, uint8_t r, uint8_t g, uint8_t b) {
    // Convert to upper case.
    if ((c >= 'a') && (c <= 'z')) {
        c += 'A'-'a';
    }

    string char_name;

    if ((c >= 'A') && (c <= 'Z')) {
        char_name = string(1, c);
    } else if ((c >= '0') && (c <= '9')) {
        char_name = string(1, c);
    }

    if (c == ':') {
        Drawing * nDrawing = new Drawing(x, y);
        Drawing * dot = BuildChar(0, 0, "filled_font/dot.txt", size, size, r, g, b);
        Drawing * dot2 = BuildChar(0, 0, "filled_font/dot.txt", size, size, r, g, b);
        nDrawing->add(dot);
        nDrawing->add(dot2);
        dot->translate(0, -size * 4);
        return nDrawing;
    } else if (c == '.') {
        const char* str = "dot";
        char_name = str;
    }

    if (char_name != "") {

        string filename = "filled_font/" + char_name + ".txt";
        return BuildChar(x, y, filename, size, size, r, g, b);
    }
    return new Drawing(x, y);
}

Drawing * createFilledCharacter(char c, float size, float x, float y, uint8_t r, uint8_t g, uint8_t b) {
    if ((c >= 'a') && (c <= 'z')) {
        c += 'A'-'a';
    }

    string char_name;

    if ((c >= 'A') && (c <= 'Z')) {
        char_name = string(1, c);
    } else if ((c >= '0') && (c <= '9')) {
        char_name = string(1, c);
    }

    if (c == ':') {
        Drawing * nDrawing = new Drawing(x, y);
        Drawing * dot = BuildCharFilled(0, 0, "filled_font/dot.txt", size, size, r, g, b);
        Drawing * dot2 = BuildCharFilled(0, 0, "filled_font/dot.txt", size, size, r, g, b);
        nDrawing->add(dot);
        nDrawing->add(dot2);
        dot->translate(0, -size * 4);
        return nDrawing;
    } else if (c == '.') {
        const char* str = "dot";
        char_name = str;
    }

    if (char_name != "") {

        string filename = "filled_font/" + char_name + ".txt";
        return BuildCharFilled(x, y, filename, size, size, r, g, b);
    }
    return new Drawing(x, y);
}

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