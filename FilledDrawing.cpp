#include "FilledDrawing.h"
#include "FloodFill.h"
#include "Line.h"
#include <iostream>

FilledDrawing::FilledDrawing(float x, float y, uint8_t r, uint8_t g, uint8_t b) : Drawing(x, y) {
    fill_r = r;
    fill_g = g;
    fill_b = b;
}
FilledDrawing::FilledDrawing(const FilledDrawing& drawing) : Drawing(drawing.origin.getX(), drawing.origin.getY()) {
    for (auto& drawable : drawing.drawables) {
        Drawable * cloned = drawable->clone();
        drawables.push_back(cloned);
        Line * p_line = dynamic_cast<Line*>(cloned);
        if (p_line != nullptr) {
            lines.push_back(p_line);
        }
        // Recalculate boundary.
        float min_x = cloned->minBoundary().getX();
        float min_y = cloned->minBoundary().getY();
        float max_x = cloned->maxBoundary().getX();
        float max_y = cloned->maxBoundary().getY();
        if (min_x < _minBoundary.getX()) {
        _minBoundary.setX(min_x);
        }
        if (min_y < _minBoundary.getY()) {
        _minBoundary.setY(min_y);
        }
        if (max_x > _maxBoundary.getX()) {
        _maxBoundary.setX(max_x);
        }
        if (max_y > _maxBoundary.getY()) {
        _maxBoundary.setY(max_y);
        };
    }
    fill_r = drawing.fill_r;
    fill_g = drawing.fill_g;
    fill_b = drawing.fill_b;
}
Drawable * FilledDrawing::clone() {
    return new FilledDrawing(*this);
}

void FilledDrawing::add (Drawable *drawable) {
    Drawing::add(drawable);
    Line * p_line = dynamic_cast<Line*>(drawable);
    if (p_line != nullptr) {
        lines.push_back(p_line);
    }
}

void FilledDrawing::remove (Drawable *drawable) {
    Drawing::remove(drawable);
    Line * p_line = dynamic_cast<Line*>(drawable);
    if (p_line != nullptr) {
        lines.erase(std::remove(lines.begin(), lines.end(), p_line), lines.end());
    }
}

void FilledDrawing::translate (float translate_x, float translate_y) {
    Drawing::translate(translate_x, translate_y);
}
void FilledDrawing::scale (float scale_x, float scale_y, float origin_x, float origin_y) {
    Drawing::scale(scale_x, scale_y, origin_x, origin_y);
}
void FilledDrawing::rotate (float angle, float origin_x, float origin_y) {
    Drawing::rotate(angle, origin_x, origin_y);
}

void FilledDrawing::draw(FrameBuffer& frameBuffer) {
    // Drawing::draw(frameBuffer);
    int o_x = minBoundary().getX();
    int o_y = minBoundary().getY();
    int m_x = maxBoundary().getX();
    int m_y = maxBoundary().getY();
    int left = 0;
    int right = frameBuffer.getWidth();
    int top = 0;
    int bottom = frameBuffer.getHeight();
    // Draw using raycasting/scanline.
    // if ((m_x >= left) && (m_y >= top) && (o_x <= right) && (o_y <= bottom)) {
    //     intersectionMap.calculateIntersections(lines);
    //     if ((intersectionMap.getWidth() > 0) && (intersectionMap.getHeight() > 0)) {
    //         u_int32_t color = frameBuffer.getColor(fill_r, fill_g, fill_b);
    //         int o_y = intersectionMap.getY();
    //         int o_x = intersectionMap.getX();
    //         for (int y = 0; y < intersectionMap.getHeight(); y++) {
    //             int t_y = o_y + y;
    //             bool drawing = intersectionMap.getPoint(o_x, t_y);
    //             for (int x = 1; x < intersectionMap.getWidth(); x++) {
    //                 int t_x = o_x + x;
    //                 if (intersectionMap.getPoint(t_x, t_y)) {
    //                     drawing = !drawing;
    //                     //frameBuffer.setPixel(t_x, t_y, color);
    //                 } else if (drawing) {
    //                     frameBuffer.setPixel(t_x, t_y, color);
    //                 }
    //             }
    //         }
    //     }
    // }
    if ((m_x >= left) && (m_y >= top) && (o_x <= right) && (o_y <= bottom)) {
        intersectionMap.calculateIntersections(lines);
        intersectionMap.floodFill();
        u_int32_t color = frameBuffer.getColor(fill_r, fill_g, fill_b);
        int o_y = intersectionMap.getY();
        int o_x = intersectionMap.getX();
        for (int y = 0; y < intersectionMap.getHeight(); y++) {
            int t_y = o_y + y;
            bool drawing = intersectionMap.getPoint(o_x, t_y);
            for (int x = 1; x < intersectionMap.getWidth(); x++) {
                int t_x = o_x + x;
                if (intersectionMap.getPoint(t_x, t_y)) {
                    frameBuffer.setPixel(t_x, t_y, color);
                }
            }
        }
    }
}
void FilledDrawing::clippedDraw(FrameBuffer& frameBuffer, float left, float top, float right, float bottom) {
    Drawing::clippedDraw(frameBuffer, left, top, right, bottom);
    int o_x = minBoundary().getX();
    int o_y = minBoundary().getY();
    int m_x = maxBoundary().getX();
    int m_y = maxBoundary().getY();
    if ((m_x >= left) && (m_y >= top) && (o_x <= right) && (o_y <= bottom)) {
        intersectionMap.calculateIntersections(lines);
        intersectionMap.floodFill();
        if ((intersectionMap.getWidth() > 0) && (intersectionMap.getHeight() > 0)) {
            int width = intersectionMap.getWidth();
            int height = intersectionMap.getHeight();
            o_y = intersectionMap.getY();
            o_x = intersectionMap.getX();
            m_y = intersectionMap.getY() + height;
            m_x = intersectionMap.getX() + width;
            u_int32_t color = frameBuffer.getColor(fill_r, fill_g, fill_b);
            if ((m_x < left) || (m_y < top) || (o_x > right) || (o_y > bottom)) {
                // Draws nothing.
            } else if ((o_x >= left) && (o_y >= top) && (m_x < right) && (m_y < top)) { // Draws normally.
                // for (int y = 0; y < height; y++) {
                //     int t_y = o_y + y;
                //     bool drawing = intersectionMap.getPoint(o_x, t_y);
                //     bool prev = drawing;
                //     for (int x = 1; x < width; x++) {
                //         int t_x = o_x + x;
                //         if ((intersectionMap.getPoint(t_x, t_y)) && (!prev)) {
                //             drawing = !drawing;
                //             //frameBuffer.setPixel(t_x, t_y, color);
                //         } else if (drawing) {
                //             frameBuffer.setPixel(t_x, t_y, color);
                //         }
                //         prev = intersectionMap.getPoint(t_x, t_y);
                //     }
                // }
                for (int y = 0; y < height; y++) {
                    int t_y = o_y + y;
                    bool drawing = intersectionMap.getPoint(o_x, t_y);
                    for (int x = 1; x < width; x++) {
                        int t_x = o_x + x;
                        if (intersectionMap.getPoint(t_x, t_y)) {
                            frameBuffer.setPixel(t_x, t_y, color);
                        }
                    }
                }
            } else {
                int s_y = 0;
                if (o_y < top) {
                    s_y = top - o_y;
                }
                int e_y = height;
                if (m_y > bottom) {
                    e_y = bottom - o_y;
                }
                int s_x = 0;
                if (o_x < left) {
                    s_x = left - o_x;
                }
                int e_x = width;
                if (m_x > right) {
                    e_x = right - o_x;
                }
                // int x, y, t_y, t_x, idx;
                // bool * starting = new bool[e_y - s_y];
                // bool prev = false;
                // for (y = s_y; y < e_y; y++) {
                //     t_y = o_y + y;
                //     idx = y - s_y;
                //     starting[idx] = intersectionMap.getPoint(o_x, t_y);
                //     prev = starting[idx];
                //     for (x = 1; x <= s_x; x++) {
                //         t_x = o_x + x;
                //         if ((intersectionMap.getPoint(t_x, t_y)) && (!prev)) {

                //             starting[idx] = !starting[idx];
                //         }
                //         prev = intersectionMap.getPoint(t_x, t_y);
                //     }
                // }
                // bool drawing = false;
                // for (y = s_y; y < e_y; y++) {
                //     t_y = o_y + y;
                //     idx = y - s_y;
                //     drawing = starting[idx];
                //     prev = starting[idx];
                //     // drawing = intersectionMap.getPoint(o_x, t_y);
                //     for (x = s_x + 1; x < e_x; x++) {
                //     // for (x = 1; x < e_x; x++) {
                //         t_x = o_x + x;
                //         if (intersectionMap.getPoint(t_x, t_y) && (!prev)) {
                //             drawing = !drawing;
                //             //frameBuffer.setPixel(t_x, t_y, color);
                //         } else if (drawing) {
                //             frameBuffer.setPixel(t_x, t_y, color);
                //         }
                //         prev = intersectionMap.getPoint(t_x, t_y);
                //     }
                // }
                // delete[] starting;
                for (int y = s_y; y < e_y; y++) {
                    int t_y = o_y + y;
                    bool drawing = intersectionMap.getPoint(o_x, t_y);
                    for (int x = s_x; x < e_x; x++) {
                        int t_x = o_x + x;
                        if (intersectionMap.getPoint(t_x, t_y)) {
                            frameBuffer.setPixel(t_x, t_y, color);
                        }
                    }
                }
            }
        }
    }

}