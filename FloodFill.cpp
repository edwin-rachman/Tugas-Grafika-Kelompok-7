#include "FloodFill.h"
#include "Point.h"
#include <queue>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

bool isInBound(int lt_x, int lt_y, int br_x, int br_y, int x, int y) {
    return ((x >= lt_x) && (y >= lt_y) && (x < br_x) && (y < br_y));
}

int index(int lt_x, int lt_y, int br_x, int br_y, int x, int y) {
    return (x - lt_x) + ((y - lt_y) * (br_x - lt_x));
}

void FloodFill(FrameBuffer& frameBuffer, int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    FloodFill(frameBuffer, 0, 0, frameBuffer.getWidth(), frameBuffer.getHeight(), x, y, r, g, b);
}

void FloodFill(FrameBuffer& frameBuffer, int x, int y, uint32_t rgb) {
    FloodFill(frameBuffer, 0, 0, frameBuffer.getWidth(), frameBuffer.getHeight(), x, y, rgb);
}

void FloodFill(FrameBuffer& frameBuffer, int lt_x, int lt_y, int br_x, int br_y, int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    FloodFill(frameBuffer, lt_x, lt_y, br_x, br_y, x, y, frameBuffer.getColor(r, g, b));
}

void FloodFill(FrameBuffer& frameBuffer, int lt_x, int lt_y, int br_x, int br_y, int x, int y, uint32_t color) {
    queue<Point> next;
    int size = (br_x - lt_x) * (br_y - lt_y);
    bool * processed = new bool[size];
    // Process consuming.
    for (int j = 0; j < size; j++) {
        processed[j] = false;
    }
    Point origin(x, y);
    next.push(origin);
    // Depth first flood filling.
    while (!next.empty()) {
        Point curr = next.front();
        next.pop();
        int i = index(lt_x, lt_y, br_x, br_y, curr.getX(), curr.getY());
        if (!processed[i]) {
            processed[i] = true;
            if ((isInBound(lt_x, lt_y, br_x, br_y, curr.getX(), curr.getY())) && (frameBuffer.getPixel(curr.getX(), curr.getY()) == 0)) {
                frameBuffer.setPixel(curr.getX(), curr.getY(), color);
                Point up(curr.getX(), curr.getY() + 1);
                if (isInBound(lt_x, lt_y, br_x, br_y, up.getX(), up.getY())) {
                    i = index(lt_x, lt_y, br_x, br_y, up.getX(), up.getY());
                    if (!processed[i]) {
                        next.push(up);
                    }
                }
                Point down(curr.getX(), curr.getY() - 1);
                if (isInBound(lt_x, lt_y, br_x, br_y,  down.getX(), down.getY())) {
                    i = index(lt_x, lt_y, br_x, br_y, down.getX(), down.getY());
                    if (!processed[i]) {
                        next.push(down);
                    }
                }
                Point left(curr.getX() - 1, curr.getY());
                if (isInBound(lt_x, lt_y, br_x, br_y, left.getX(), left.getY())) {
                    i = index(lt_x, lt_y, br_x, br_y, left.getX(), left.getY());
                    if (!processed[i]) {
                        next.push(left);
                    }
                }
                Point right(curr.getX() + 1, curr.getY());
                if (isInBound(lt_x, lt_y, br_x, br_y, right.getX(), right.getY())) {
                    i = index(lt_x, lt_y, br_x, br_y, right.getX(), right.getY());
                    if (!processed[i]) {
                        next.push(right);
                    }
                }
            }
        }
    }
    delete[] processed;
}