#include <iostream>
#include <ctime>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <random>
#include "Line.h"
#include "Drawing.h"
#include "FilledDrawing.h"
#include "FloodFill.h"
#include "KeyboardInputListener.h"
#include "MouseInputListener.h"
#include "CharBuilder.h"
#include "Image.h"
#include "ShapeBuilder.h"
#include "TextObject.h"
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

    Drawable * minimap = root.clone();

    float m_size_x = minimap->maxBoundary().getX() - minimap->minBoundary().getX();
    float m_size_y = minimap->maxBoundary().getY() - minimap->minBoundary().getY();
    
    float minimap_scale = 100.0f / m_size_y;
    minimap->scale(minimap_scale, minimap_scale, 0, 0);

    Drawing * minimap_background = createFilledBox(minimap->minBoundary().getX(), minimap->minBoundary().getY(), minimap->maxBoundary().getX(), minimap->maxBoundary().getY(), 0x20, 0x20, 0x20);

    m_size_x *= minimap_scale;
    m_size_y *= minimap_scale;

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

    FilledDrawing crosshair(0, 0, 0xFF, 0xFF, 0xFF);
    // Drawing crosshair(0, 0);
    crosshair.add(new Line(0, 8, 0, 0, 0x00, 0x00, 0x00));
    crosshair.add(new Line(0, 8, 2, 6, 0x00, 0x00, 0x00));
    crosshair.add(new Line(2, 6, 5, 10, 0x00, 0x00, 0x00));
    crosshair.add(new Line(5, 10, 7, 8.5f, 0x00, 0x00, 0x00));
    crosshair.add(new Line(7, 8.5f, 4.2f, 5, 0x00, 0x00, 0x00));
    crosshair.add(new Line(7, 4, 4.2f, 5, 0x00, 0x00, 0x00));
    crosshair.add(new Line(0, 0, 7, 4, 0x00, 0x00, 0x00));
    crosshair.translate(frameBuffer.getWidth() / 2, frameBuffer.getHeight() / 2);
    crosshair.scale(1.5f, 1.5f, crosshair.getOrigin().getX(), crosshair.getOrigin().getY());

    Drawing frame(0, 0);
    frame.add(new Line(left, top, right, top, 0x00, 0x00, 0xFF));
    frame.add(new Line(right, top, right, bottom, 0x00, 0x00, 0xFF));
    frame.add(new Line(right, bottom, left, bottom, 0x00, 0x00, 0xFF));
    frame.add(new Line(left, bottom, left, top, 0x00, 0x00, 0xFF));

    Drawing plane(0, 0);
    plane.add(BuildCharFilled(0, 0, "assets/plane.txt", 5, 5, 0xCC, 0xEA, 0xBC));
    plane.scale(0.75f, 0.75f, plane.getOrigin().getX(), plane.getOrigin().getY());

    Drawing bombs(0, 0);

    // root.add(&plane);
    float plane_x = plane.getOrigin().getX();
    float plane_y = plane.getOrigin().getY();
    bool show_b = false;
    int color = 0;

    float cx, cy;

    bool plane_moving = false;
    float plane_rotation = 0.5f * PI;

    float dest_plane_x = plane_x;
    float dest_plane_y = plane_y;
    float plane_speed = 10;

    bool m_right_clicked = false;
    bool m_left_clicked = false;
    int toBombCount = 0;
    const float bombRadius = 20;
    const float bombScatter = 20;
    const int bombInterval = 2;
    const int bombPerlaunch = 1;
    int bombTick = 0;
    int bombCount = 0;

    Drawing * tes0 = createCharacter('a', 5, 100, 30, 0x00, 0xFF, 0x00);
    Drawing * tes1 = createCharacter(':', 5, 150, 30, 0x00, 0xFF, 0x00);
    Drawing * tes2 = createFilledCharacter(':', 5, 200, 30, 0x00, 0xFF, 0x00);
    Text * tes3 = new Text("bomb:", 5, 250, 30, 0x00, 0xFF, 0x00);

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
                    scale *= d_scale;
                    cx = left + (right - left)/2;
                    cy = top + (bottom - top)/2;
                    pos_x = (pos_x - cx) / d_scale + cx;
                    pos_y = (pos_y - cy) / d_scale + cy;
                    dest_plane_x = (dest_plane_x - cx) / d_scale + cx;
                    dest_plane_y = (dest_plane_y - cy) / d_scale + cy;
                    root.scale(1/d_scale, 1/d_scale, cx, cy);
                    plane.scale(1/d_scale, 1/d_scale, cx, cy);
                    bombs.scale(1/d_scale, 1/d_scale, cx, cy);
                    cursor.scale(d_scale, d_scale, cursor.getOrigin().getX() + (b_size_x * cursor_scale) / 2, cursor.getOrigin().getY() + (b_size_y * cursor_scale) / 2);
                    cursor_scale_x *= d_scale;
                    cursor_scale_y *= d_scale;
                    cursor_scale *= d_scale;
                    break;
                case 122: // Z Key
                    scale /= d_scale;
                    cx = left + (right - left)/2;
                    cy = top + (bottom - top)/2;
                    pos_x = (pos_x - cx) * d_scale + cx;
                    pos_y = (pos_y - cy) * d_scale + cy;
                    dest_plane_x = (dest_plane_x - cx) * d_scale + cx;
                    dest_plane_y = (dest_plane_y - cy) * d_scale + cy;
                    root.scale(d_scale, d_scale, cx, cy);
                    plane.scale(d_scale, d_scale, cx, cy);
                    bombs.scale(d_scale, d_scale, cx, cy);
                    cursor.scale(1/d_scale, 1/d_scale, cursor.getOrigin().getX() + (b_size_x * cursor_scale) / 2, cursor.getOrigin().getY() + (b_size_y * cursor_scale) / 2);
                    cursor_scale_x /= d_scale;
                    cursor_scale_y /= d_scale;
                    cursor_scale /= d_scale;
                    break;
                case 97: // A key
                    pos_x += move_speed;
                    dest_plane_x += move_speed;
                    root.translate(move_speed, 0);
                    plane.translate(move_speed, 0);
                    bombs.translate(move_speed, 0);
                    cursor.translate(-move_speed * cursor_scale_x, 0);
                    break;
                case 100: // D key
                    pos_x -= move_speed;
                    dest_plane_x -= move_speed;
                    root.translate(-move_speed, 0);
                    plane.translate(-move_speed, 0);
                    bombs.translate(-move_speed, 0);
                    cursor.translate(move_speed * cursor_scale_x, 0);
                    break;
                case 119: // W key
                    pos_y += move_speed;
                    dest_plane_y += move_speed;
                    root.translate(0, move_speed);
                    plane.translate(0, move_speed);
                    bombs.translate(0, move_speed);
                    cursor.translate(0, -move_speed * cursor_scale_y);
                    break;
                case 115: // S key
                    pos_y -= move_speed;
                    dest_plane_y -= move_speed;
                    root.translate(0, -move_speed);
                    plane.translate(0, -move_speed);
                    bombs.translate(0, -move_speed);
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
                if (!m_right_clicked) { // OnDown.

                }
                m_right_clicked = true;
            } else {
                if (m_right_clicked) { // OnUp.
                    if (toBombCount == 0) {
                        toBombCount = bombPerlaunch;
                    }
                }
                m_right_clicked = false;
            }
            if (mouseInputListener.isLeftClicked() && x >= left && x <= right && y >= top && y <= bottom) {
                dest_plane_x = x;
                dest_plane_y = y;
                plane_moving = true;
                //root.add(BuildCharFilled(x - pos_x, y - pos_y, "brush/square.txt", 1, 1, r, g, b));
                m_left_clicked = true;
            } else {
                m_left_clicked = false;
                tes3->setText("bb");
            }
        }

        if (toBombCount > 0) {
            bombTick++;
            if (bombTick >= bombInterval) {
                float tx = plane.getOrigin().getX();
                float ty = plane.getOrigin().getY();
                cx = bombs.getOrigin().getX();
                cy = bombs.getOrigin().getY();
                float offset_x = (((float)rand())/RAND_MAX - 0.5f) * bombScatter / scale;
                float offset_y = (((float)rand())/RAND_MAX - 0.5f) * bombScatter / scale;
                Drawing * bomb = createFilledCircle((tx - cx) + offset_x, (ty - cy) + offset_y, bombRadius, 0xFF, 0x00, 0x00, 18);
                bomb->scale(1.0f/scale, 1.0f/scale, bomb->getOrigin().getX(), bomb->getOrigin().getY());
                bombs.add(bomb);
                toBombCount--;
                bombTick = 0;
                bombCount++;
            }
        }

        frameBuffer.fill(frameBuffer.getColor(0x40, 0x40, 0x40));

        if (show_b) {
            b_image.draw(frameBuffer);
        }
        root.clippedDraw(frameBuffer, left, top, right, bottom);
        minimap_background->draw(frameBuffer);
        minimap->draw(frameBuffer);
        cursor.clippedDraw(frameBuffer, minimap->minBoundary().getX(), minimap->minBoundary().getY(), minimap->maxBoundary().getX(), minimap->maxBoundary().getY());
        bombs.clippedDraw(frameBuffer, left, top, right, bottom);
        plane.clippedDraw(frameBuffer, left, top, right, bottom);
        frame.draw(frameBuffer);
        tes0->draw(frameBuffer);
        tes1->draw(frameBuffer);
        tes2->draw(frameBuffer);
        tes3->draw(frameBuffer);
        //plane.draw(frameBuffer);

        plane_x = plane.getOrigin().getX();
        plane_y = plane.getOrigin().getY();
        if ((plane_moving) && ((abs(plane_x - dest_plane_x) > numeric_limits<float>::epsilon()) || (abs(plane_y - dest_plane_y) > numeric_limits<float>::epsilon()))) {
            // Moves plane.
            float pdx = dest_plane_x - plane_x;
            float pdy = dest_plane_y - plane_y;
            float dist = sqrt((pdx * pdx) + (pdy * pdy));
            float tentative_speed = plane_speed / scale;
            if (dist < plane_speed) {
                tentative_speed = dist;
            }
            float angle = atan2(pdy, pdx);
            plane.rotate(angle - plane_rotation, plane_x, plane_y);
            plane_rotation = angle;
            pdx = cos(angle) * tentative_speed;
            pdy = sin(angle) * tentative_speed;
            plane.translate(pdx, pdy);
        } else {
            plane_moving = false;
        }

        crosshair.draw(frameBuffer);
        frameBuffer.swapBuffers();
    }

    keyboardInputListener.stop();
    mouseInputListener.stop();
}
