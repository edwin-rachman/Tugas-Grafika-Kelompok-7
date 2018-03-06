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
    
    FilledDrawing root(0, 0, 0xFF, 0xFF, 0xFF);
    //Drawing root(0, 0);

    root.add(new Line(0, 0, 10, 0, 0xFF, 0xFF, 0xFF));
    root.add(new Line(10, 0, 10, 10, 0xFF, 0xFF, 0xFF));
    //root.add(new Line(10, 10, 0, 10, 0xFF, 0xFF, 0xFF));
    root.add(new Line(0, 10, 0, 0, 0xFF, 0xFF, 0xFF));
    root.add(new Line(0, 10, 5, 15, 0xFF, 0xFF, 0xFF));
    root.add(new Line(5, 15, 10, 10, 0xFF, 0xFF, 0xFF));
    
    bool running = true;

    float left = 100;
    float top = 100;
    float right = frameBuffer.getWidth()-100;
    float bottom = frameBuffer.getHeight()-100;

    float move_speed = 5;

    float scale = 1;
    float d_scale = 1.05f;
    //float sc = 1.33f;
    //root.scale(sc, sc, root.getOrigin().getX(), root.getOrigin().getY());

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
                    root.scale(1/d_scale, 1/d_scale, left + (right - left)/2, top + (bottom - top)/2);
                    break;
                case 122: // Z Key
                    scale *= d_scale;
                    root.scale(d_scale, d_scale, left + (right - left)/2, top + (bottom - top)/2);
                    break;
                case 97: // A key
                    pos_x += move_speed;
                    root.translate(move_speed, 0);
                    break;
                case 100: // D key
                    pos_x -= move_speed;
                    root.translate(-move_speed, 0);
                    break;
                case 119: // W key
                    pos_y += move_speed;
                    root.translate(0, move_speed);
                    break;
                case 115: // S key
                    pos_y -= move_speed;
                    root.translate(0, -move_speed);
                    break;
            }
        }
        
        frameBuffer.fill(frameBuffer.getColor(0x10, 0x10, 0x10));

        root.clippedDraw(frameBuffer, left, top, right, bottom);
        // root.draw(frameBuffer);
        frameBuffer.swapBuffers();
    }
    
    keyboardInputListener.stop();
}
