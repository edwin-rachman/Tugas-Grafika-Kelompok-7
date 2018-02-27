#include <iostream>
#include <ctime>
#include <fstream>
#include "Line.h"
#include "Drawing.h"
#include "FilledDrawing.h"
#include "FloodFill.h"
#include "KeyboardInputListener.h"
#include "CharBuilder.h"
#include "Image.h"
using namespace std;

const float PI = std::acos(-1);

int main() {
    std::cout << "\e[?25l" << std::flush;
    FrameBuffer frameBuffer("/dev/fb0");
    
    KeyboardInputListener keyboardInputListener(0, 33333);
    keyboardInputListener.start();
    
    Drawing root(0, 0);

    ifstream stream("peta.txt", ifstream::in);
    int w, h, count;
    stream >> w;
    stream >> h;
    count = w * h * 3;
    uint8_t * bytes = new uint8_t[count];
    for (int i = 0; i < count; i++) {
        int v;
        stream >> v;
        bytes[i] = (uint8_t) v;
    }
    stream.close();

    Drawing b_image(-6, -207);
    Image image(0, 0, bytes, w, h, 3);

    b_image.add(&image);
    
    Drawing layout(0, 0);
    layout.add(BuildChar(0, 0, "itb/layout.txt", 1, 1, 0x99, 0x99, 0x99));
    root.add(&layout);

    Drawing buildings(0, 0);
    for (int i = 2; i <= 65; i++) {
        buildings.add(BuildChar(0, 0, "buildings/scrapped_" + to_string(i) + ".txt", 1, 1, 0xFF, 0xFF, 0xFF));
    }
    root.add(&buildings);
    Drawing assembly_points(0, 0);
    for (int i = 66; i <= 81; i++) {
        assembly_points.add(BuildChar(0, 0, "assembly_points/scrapped_" + to_string(i) + ".txt", 1, 1, 0xFF, 0xAA, 0x00));
    }
    root.add(&assembly_points);
    
    bool running = true;

    float left = 0;
    float top = 0;
    float right = frameBuffer.getWidth();
    float bottom = frameBuffer.getHeight();

    float move_speed = 5;

    float scale = 1;
    float d_scale = 1.05f;
    float sc = 1.33f;
    root.scale(sc, sc, root.getOrigin().getX(), root.getOrigin().getY());

    float size_x = root.maxBoundary().getX() - root.minBoundary().getX();
    float size_y = root.maxBoundary().getY() - root.minBoundary().getY();

    float pos_x = (frameBuffer.getWidth() - size_x) / 2;
    float pos_y = (frameBuffer.getHeight() - size_y) / 2;
    // float pos_x = 0;
    // float pos_y = 0;

    root.translate(pos_x, pos_y);

    bool show_b = false;

    while (running) {
        if (keyboardInputListener.receivedInput()) {
            switch (keyboardInputListener.getInput()) {
                case 27: // Escape
                    running = false;
                    break;
                case 99: // C key
                    // show_b = !show_b;
                    break;
                case 120: // X Key
                    scale /= d_scale;
                    root.scale(1/d_scale, 1/d_scale, root.getOrigin().getX(), root.getOrigin().getY());
                    break;
                case 122: // Z Key
                    scale *= d_scale;
                    root.scale(d_scale, d_scale, root.getOrigin().getX(), root.getOrigin().getY());
                    break;
                case 97: // A key
                    pos_x -= move_speed;
                    root.translate(-move_speed, 0);
                    break;
                case 100: // D key
                    pos_x += move_speed;
                    root.translate(move_speed, 0);
                    break;
                case 119: // W key
                    pos_y -= move_speed;
                    root.translate(0, -move_speed);
                    break;
                case 115: // S key
                    pos_y += move_speed;
                    root.translate(0, move_speed);
                    break;
            }
        }
        
        frameBuffer.fill(frameBuffer.getColor(0x10, 0x10, 0x10));

        if (show_b) {
            b_image.draw(frameBuffer);
        }
        root.clippedDraw(frameBuffer, left, top, right, bottom);

        frameBuffer.swapBuffers();
    }
    
    keyboardInputListener.stop();
}
