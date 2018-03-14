#include "TextObject.h"
#include "ShapeBuilder.h"
#include <string>
using namespace std;

Text::Text(string text, float size, float x, float y, uint8_t r, uint8_t g, uint8_t b) : Drawing(x, y) {
    this->size = size;
    red = r;
    green = g;
    blue = b;
    setText(text);
}

void Text::setText(string text) {
    this->text = text;
    vector<Drawing *>::iterator it = characters.begin();
    for (it; it < characters.end(); it++) {
        delete *it;
    }
    drawables.clear();
    characters.clear();
    float offset = 0;
    float r_size = size * 9;
    for (int i = 0; i < text.size(); i++) {
        Drawing * character = createFilledCharacter(text[i], size, offset, 0, red, green, blue);
        characters.push_back(character);
        add(character);
        // offset += character->maxBoundary().getX() - character->minBoundary().getX() + size;
        offset += r_size;
    }
}

string Text::getText() {
    return text;
}