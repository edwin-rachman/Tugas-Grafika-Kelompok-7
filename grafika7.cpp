#include <iostream>
#include <ctime>
#include <fstream>
#include "Line.h"
#include "Drawing.h"
#include "FilledDrawing.h"
#include "FloodFill.h"
#include "KeyboardInputListener.h"
#include "MouseInputListener.h"
#include "CharBuilder.h"
#include "Image.h"
using namespace std;

const float PI = std::acos(-1);

int main() {
    std::cout << "\e[?25l" << std::flush;
    FrameBuffer frameBuffer("/dev/fb0");
    
    KeyboardInputListener keyboardInputListener(0, 3333);
    keyboardInputListener.start();
    
    MouseInputListener mouseInputListener(frameBuffer.getWidth() / 2, frameBuffer.getHeight() / 2);
    mouseInputListener.start();
    
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
        buildings.add(BuildCharFilled(0, 0, "buildings/scrapped_" + to_string(i) + ".txt", 1, 1, 0xFF, 0xFF, 0xFF));
    }
    root.add(&buildings);
    Drawing assembly_points(0, 0);
    for (int i = 66; i <= 81; i++) {
        assembly_points.add(BuildCharFilled(0, 0, "assembly_points/scrapped_" + to_string(i) + ".txt", 1, 1, 0xFF, 0xAA, 0x00));
    }
    root.add(&assembly_points);
    
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
	
    float minimap_scale = 0.25f;
    Drawable * minimap = root.clone();
    minimap->scale(minimap_scale, minimap_scale, 0, 0);
    
    float m_size_x = minimap->maxBoundary().getX() - minimap->minBoundary().getX();
    float m_size_y = minimap->maxBoundary().getY() - minimap->minBoundary().getY();

    float b_size_x = ((right - left) / size_x) * m_size_x;
    float b_size_y = ((bottom - top) / size_y) * m_size_y;

    float cursor_scale_x = m_size_x / size_x;
    float cursor_scale_y = m_size_y / size_y;
    float cursor_scale = 1;

    Drawing cursor(0, 0);
    cursor.add(new Line(0, 0, b_size_x, 0, 0x00, 0xFF, 0x00));
    cursor.add(new Line(b_size_x, 0, b_size_x, b_size_y, 0x00, 0xFF, 0x00));
    cursor.add(new Line(b_size_x, b_size_y, 0, b_size_y, 0x00, 0xFF, 0x00));
    cursor.add(new Line(0, b_size_y, 0, 0, 0x00, 0xFF, 0x00));

    cursor.translate((m_size_x - b_size_x) / 2, (m_size_y - b_size_y) / 2);
    root.translate(pos_x, pos_y);
    
    Drawing crosshair(0, 0);
    crosshair.add(new Line(0, -5, 0, -2, 0x00, 0x00, 0x00));
    crosshair.add(new Line(0, 5, 0, 2, 0x00, 0x00, 0x00));
    crosshair.add(new Line(5, 0, 2, 0, 0x00, 0x00, 0x00));
    crosshair.add(new Line(-5, 0, -2, 0, 0x00, 0x00, 0x00));
    crosshair.translate(frameBuffer.getWidth() / 2, frameBuffer.getHeight() / 2);

    Drawing frame(0, 0);
    frame.add(new Line(left, top, right, top, 0x00, 0x00, 0xFF));
    frame.add(new Line(right, top, right, bottom, 0x00, 0x00, 0xFF));
    frame.add(new Line(right, bottom, left, bottom, 0x00, 0x00, 0xFF));
    frame.add(new Line(left, bottom, left, top, 0x00, 0x00, 0xFF));
    
    bool show_b = false;
    int color = 0;

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
                    cursor.scale(d_scale, d_scale, cursor.getOrigin().getX() + (b_size_x * cursor_scale) / 2, cursor.getOrigin().getY() + (b_size_y * cursor_scale) / 2);
                    cursor_scale_x *= d_scale;
                    cursor_scale_y *= d_scale;
                    cursor_scale *= d_scale;
                    break;
                case 122: // Z Key
                    scale *= d_scale;
                    root.scale(d_scale, d_scale, left + (right - left)/2, top + (bottom - top)/2);
                    cursor.scale(1/d_scale, 1/d_scale, cursor.getOrigin().getX() + (b_size_x * cursor_scale) / 2, cursor.getOrigin().getY() + (b_size_y * cursor_scale) / 2);
                    cursor_scale_x /= d_scale;
                    cursor_scale_y /= d_scale;
                    cursor_scale /= d_scale;
                    break;
                case 97: // A key
                    pos_x += move_speed;
                    root.translate(move_speed, 0);
                    cursor.translate(-move_speed * cursor_scale_x, 0);
                    break;
                case 100: // D key
                    pos_x -= move_speed;
                    root.translate(-move_speed, 0);
                    cursor.translate(move_speed * cursor_scale_x, 0);
                    break;
                case 119: // W key
                    pos_y += move_speed;
                    root.translate(0, move_speed);
                    cursor.translate(0, -move_speed * cursor_scale_y);
                    break;
                case 115: // S key
                    pos_y -= move_speed;
                    root.translate(0, -move_speed);
                    cursor.translate(0, move_speed * cursor_scale_y);
                    break;
            }
        }
        
        if (mouseInputListener.getInput()) {
          crosshair.translate(mouseInputListener.getRelativeX(), mouseInputListener.getRelativeY());
          float x = crosshair.getOrigin().getX();
          float y = crosshair.getOrigin().getY();
          if (mouseInputListener.isRightClicked()) {
            color = (color + 1) % 8;
          }
          uint8_t r = color & 0x1 ? 0xFF: 0x00;
          uint8_t g = color & 0x2 ? 0xFF: 0x00;
          uint8_t b = color & 0x4 ? 0xFF: 0x00;
          if (mouseInputListener.isRightClicked()) {
            crosshair.setColor(r, g, b);
          }
          if (mouseInputListener.isLeftClicked() && x >= left && x <= right && y >= top && y <= bottom) {
            root.add(BuildCharFilled(x - pos_x, y - pos_y, "brush/square.txt", 1, 1, r, g, b));
          }
        }
        
        frameBuffer.fill(frameBuffer.getColor(0x40, 0x40, 0x40));

        if (show_b) {
            b_image.draw(frameBuffer);
        }
        root.clippedDraw(frameBuffer, left, top, right, bottom);
        frame.draw(frameBuffer);
        minimap->draw(frameBuffer);
        cursor.draw(frameBuffer);
        crosshair.draw(frameBuffer);
        frameBuffer.swapBuffers();
    }
    
    keyboardInputListener.stop();
    mouseInputListener.stop();
}