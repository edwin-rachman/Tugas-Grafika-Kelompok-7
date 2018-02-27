#ifndef IMAGE_H
#define IMAGE_H

#include "FrameBuffer.h"
#include "Point.h"
#include "Drawable.h"
#include <string>
#include <stdint.h>

using namespace std;

class Image : public Drawable {
private:
    Point origin;
    int width, height, bpp;
    int o_width, o_height;
    string file_path;
    uint8_t * img;
public:
    Image(int x, int y, uint8_t * image, int width, int height, int bpp);
    ~Image();
    void draw(FrameBuffer& frameBuffer);
    void clippedDraw(FrameBuffer& frameBuffer, float left, float top, float right, float bottom);
    void translate(float translate_x, float translate_y);
    void scale(float scale_x, float scale_y, float origin_x, float origin_y);
    void rotate(float angle, float origin_x, float origin_y);
    Point minBoundary();
    Point maxBoundary();
    uint32_t getPixelAt(FrameBuffer& frameBuffer, int x, int y);
    Drawable *clone();
};

#endif
