#include "Image.h"
#include "Drawable.h"

Image::Image(int x, int y, uint8_t * image, int width, int height, int bpp) : origin(x, y) {
    this->file_path = file_path;
    img = image;
    this->width = width;
    this->height = height;
    this->bpp = bpp;
}

Image::~Image() {
}

uint32_t Image::getPixelAt(FrameBuffer& frameBuffer, int x, int y) {
    int location = (x * bpp) + (y * (width * bpp));
    return frameBuffer.getColor(img[location], img[location + 1], img[location + 2]);
}

void Image::draw(FrameBuffer& frameBuffer) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            frameBuffer.setPixel(origin.getX() + x, origin.getY() + y, getPixelAt(frameBuffer, x, y));
        }
    }
}
void Image::clippedDraw(FrameBuffer& frameBuffer, float left, float top, float right, float bottom) {
    draw(frameBuffer);
}
void Image::translate(float translate_x, float translate_y) {
    origin.translate(translate_x, translate_y);
}
void Image::scale(float scale_x, float scale_y, float origin_x, float origin_y) {
    origin.scale(scale_x, scale_y, origin_x, origin_y);
}
void Image::rotate(float angle, float origin_x, float origin_y) {
    origin.rotate(angle, origin_x, origin_y);
}
Point Image::minBoundary() {
    return origin;
}
Point Image::maxBoundary() {
    return Point(origin.getX() + width, origin.getY() + height);
}
Drawable * Image::clone() {
    return new Image(origin.getX(), origin.getY(), img, width, height, bpp);
}