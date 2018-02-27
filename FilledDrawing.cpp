#include "FilledDrawing.h"
#include "FloodFill.h"

FilledDrawing::FilledDrawing(float x, float y, uint8_t r, uint8_t g, uint8_t b) : Drawing(x, y) {
    fill_r = r;
    fill_g = g;
    fill_b = b;
}
FilledDrawing::FilledDrawing(const FilledDrawing& drawing) : Drawing(drawing) {
    fill_r = drawing.fill_r;
    fill_g = drawing.fill_g;
    fill_b = drawing.fill_b;
}
FilledDrawing * FilledDrawing::clone() {
    return new FilledDrawing(*this);
}
void FilledDrawing::draw(FrameBuffer& frameBuffer) {
    Drawing::draw(frameBuffer);
    int p_x = (maxBoundary().getX() - minBoundary().getX()) / 2;
    int p_y = (maxBoundary().getY() - minBoundary().getY()) / 2;
    FloodFill(frameBuffer, minBoundary().getX(), minBoundary().getY(), maxBoundary().getX(), maxBoundary().getY(), p_x, p_y, fill_r, fill_g, fill_b);
}
void FilledDrawing::clippedDraw(FrameBuffer& frameBuffer, float left, float top, float right, float bottom) {
    Drawing::clippedDraw(frameBuffer, left, top, right, bottom);
    // if ((minBoundary().getX() < right) && (minBoundary().getY() < bottom) && (maxBoundary().getX() > left) && (maxBoundary().getY() > top)) {
    //     int min_x = minBoundary().getX() < left ? left : minBoundary().getX();
    //     int min_y = minBoundary().getY() < top ? top : minBoundary().getY();
    //     int max_x = maxBoundary().getX() > right ? right : maxBoundary().getX();
    //     int max_y = maxBoundary().getY() > bottom ? bottom : maxBoundary().getY();
    //     int p_x = (max_x - min_x) / 2;
    //     int p_y = (max_y - min_y) / 2;
    //     FloodFill(frameBuffer, min_x, min_y, max_x, max_y, p_x, p_y, fill_r, fill_g, fill_b);
    // }

}