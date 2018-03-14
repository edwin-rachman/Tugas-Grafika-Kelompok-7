#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H
#include "Drawing.h"
#include <string>
#include <vector>
using namespace std;

class Text : public Drawing {
private:
    string text;
    vector<Drawing *> characters;
    float size;
    uint8_t red, green, blue;
public:
    Text(string text, float size, float x, float y, uint8_t r, uint8_t g, uint8_t b);
    ~Text();

    void setText(string text);
    string getText();
};


#endif