#include <iostream>
#include <ctime>
#include "Line.h"
#include "Drawing.h"
#include "FloodFill.h"
#include "KeyboardInputListener.h"

const float PI = std::acos(-1);

int main() {
  std::cout << "\e[?25l" << std::flush;
  FrameBuffer frameBuffer("/dev/fb0");
  
  KeyboardInputListener keyboardInputListener(0, 33333);
  keyboardInputListener.start();
  
  Drawing plane(0, 0);
  plane.add(new Line(-9, 5, -2, 5, 0x00, 0x00, 0xFF));
  plane.add(new Line(-2, 5, -1, 7, 0x00, 0x00, 0xFF));
  plane.add(new Line(-1, 7, 1, 7, 0x00, 0x00, 0xFF));
  plane.add(new Line(1, 7, 2, 5, 0x00, 0x00, 0xFF));
  plane.add(new Line(2, 5, 9, 5, 0x00, 0x00, 0xFF));
  plane.add(new Line(9, 5, 2, 3, 0x00, 0x00, 0xFF));
  plane.add(new Line(2, 3, 0, 0, 0x00, 0x00, 0xFF));
  plane.add(new Line(0, 0, -2, 3, 0x00, 0x00, 0xFF));
  plane.add(new Line(-2, 3, -9, 5, 0x00, 0x00, 0xFF));
  
  Drawing pilot(0, 0);
  pilot.add(new Line(-0.5f, 0, 0, -0.65f, 0xFF, 0xFF, 0xFF));
  pilot.add(new Line(0.5f, 0, 0, -0.65f, 0xFF, 0xFF, 0xFF));
  pilot.add(new Line(0, -0.65f, 0, -1.15f, 0xFF, 0xFF, 0xFF));
  pilot.add(new Line(-0.5f, -1, 0.5f, -1, 0xFF, 0xFF, 0xFF));
  pilot.add(new Line(-0.2f, -1.2f, 0.2f, -1.2f, 0xFF, 0xFF, 0xFF));
  pilot.add(new Line(-0.2f, -1.2f, -0.2f, -1.6f, 0xFF, 0xFF, 0xFF));
  pilot.add(new Line(-0.2f, -1.6f, 0.2f, -1.6f, 0xFF, 0xFF, 0xFF));
  pilot.add(new Line(0.2f, -1.2f, 0.2f, -1.6f, 0xFF, 0xFF, 0xFF));
  pilot.rotate(-PI / 2, plane.getOrigin().getX(), plane.getOrigin().getY());
  pilot.translate(0, 5);
  
  plane.add(&pilot);
  plane.translate(0, 300);
  plane.scale(4, 4, plane.getOrigin().getX(), plane.getOrigin().getY());
  plane.rotate(PI / 2, plane.getOrigin().getX(), plane.getOrigin().getY());
  
  float left = 100;
  float top = 100;
  float right = 400;
  float bottom = 400;
  
  Drawing box(0, 0);
  box.add(new Line(left, top, right, top, 0x00, 0xFF, 0x00));
  box.add(new Line(right, top, right, bottom, 0x00, 0xFF, 0x00));
  box.add(new Line(right, bottom, left, bottom, 0x00, 0xFF, 0x00));
  box.add(new Line(left, bottom, left, top, 0x00, 0xFF, 0x00));
  
  Drawing box2(0, 0);
  box2.add(new Line(left, top, right, top, 0x00, 0xFF, 0x00));
  box2.add(new Line(right, top, right, bottom, 0x00, 0xFF, 0x00));
  box2.add(new Line(right, bottom, left, bottom, 0x00, 0xFF, 0x00));
  box2.add(new Line(left, bottom, left, top, 0x00, 0xFF, 0x00));
  box2.translate(350, 0);

  
  bool running = true;
  int time = 0;
  float scale = 1;
  
  while (running && time < 200) {
    ++time;
    if (keyboardInputListener.receivedInput()) {
      switch (keyboardInputListener.getInput()) {
        case 27:
          running = false;
        break;
        case 97:
          scale *= 6.0/5;
          plane.scale(6.0/5, 6.0/5, plane.getOrigin().getX(), plane.getOrigin().getY());
        break;
        case 100:
          scale *= 5.0/6;
          plane.scale(5.0/6, 5.0/6, plane.getOrigin().getX(), plane.getOrigin().getY());
        break;
      }
    }
    
    frameBuffer.fill(frameBuffer.getColor(0x00, 0x00, 0x00));
    box.draw(frameBuffer);
    box2.draw(frameBuffer);
    plane.clippedDraw(frameBuffer, left, top, right, bottom);
    plane.clippedDraw(frameBuffer, left + 350, top, right + 350, bottom);
    plane.translate(10, 0);
    FloodFill(frameBuffer, 0, 0, 0x36, 0xE4, 0xF9);
    // Fill from a line.
    for (int i = 12; i < 12 + (25 * scale); i += (25 * scale) / 10) {
      FloodFill(frameBuffer, plane.getOrigin().getX() - i, plane.getOrigin().getY(), 0x00, 0x00, 0xFF);
    }
    // Fill 1st box from 4 sides.
    FloodFill(frameBuffer, left, top, right, bottom, left + 1, top + 1, 0x00, 0xFF, 0x00);
    FloodFill(frameBuffer, left, top, right, bottom, right - 1, top + 1, 0x00, 0xFF, 0x00);
    FloodFill(frameBuffer, left, top, right, bottom, right - 1, bottom - 1, 0x00, 0xFF, 0x00);
    FloodFill(frameBuffer, left, top, right, bottom, left + 1, bottom - 1, 0x00, 0xFF, 0x00);
    // Fill 2nd box from 4 sides.
    FloodFill(frameBuffer, left + 350, top, right + 350, bottom, left + 1 + 350, top + 1, 0x00, 0xFF, 0x00);
    FloodFill(frameBuffer, left + 350, top, right + 350, bottom, right - 1 + 350, top + 1, 0x00, 0xFF, 0x00);
    FloodFill(frameBuffer, left + 350, top, right + 350, bottom, right - 1 + 350, bottom - 1, 0x00, 0xFF, 0x00);
    FloodFill(frameBuffer, left + 350, top, right + 350, bottom, left + 1 + 350, bottom - 1, 0x00, 0xFF, 0x00);
    frameBuffer.swapBuffers();
  }
  
  keyboardInputListener.stop();
}
