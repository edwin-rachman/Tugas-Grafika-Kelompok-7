#include <iostream>
#include <ctime>
#include "Line.h"
#include "FloodFillDrawing.h"

const float pi = std::acos(-1);

int main() {
  std::cout << "\e[?25l" << std::flush;
  FrameBuffer frameBuffer("/dev/fb0");

  timespec delay, rem;
  delay.tv_sec = 0;
  delay.tv_nsec = 33333333L;

  Drawing bullets_center(frameBuffer.getWidth() / 2, frameBuffer.getHeight());
  Drawing bullets_left(frameBuffer.getWidth() / 2, frameBuffer.getHeight());
  Drawing bullets_right(frameBuffer.getWidth() / 2, frameBuffer.getHeight());
  for (int i = 0; i < 50; ++i) {
    bullets_center.add(new Line(0, i * 50, 0, i * 50 + 14, 0xFF, 0x00, 0x00));
    bullets_left.add(new Line(i * 40, i * 40, i * 40 + 10, i * 40 + 10, 0xFF, 0x00, 0x00));
    bullets_right.add(new Line(-i * 40, i * 40, -i * 40 - 10, i * 40 + 10, 0xFF, 0x00, 0x00));
  }

  Drawing rotor(0, 0);
  rotor.add(new Line(-2, -2, 2, 2, 0x00, 0xFF, 0x00));

  Drawing plane(0, 0);
  plane.add(new Line(-9, 5, -2, 5, 0x00, 0xFF, 0x00));
  plane.add(new Line(-2, 5, -1, 7, 0x00, 0xFF, 0x00));
  plane.add(new Line(-1, 7, 1, 7, 0x00, 0xFF, 0x00));
  plane.add(new Line(1, 7, 2, 5, 0x00, 0xFF, 0x00));
  plane.add(new Line(2, 5, 9, 5, 0x00, 0xFF, 0x00));
  plane.add(new Line(9, 5, 2, 3, 0x00, 0xFF, 0x00));
  plane.add(new Line(2, 3, 0, 0, 0x00, 0xFF, 0x00));
  plane.add(new Line(0, 0, -2, 3, 0x00, 0xFF, 0x00));
  plane.add(new Line(-2, 3, -9, 5, 0x00, 0xFF, 0x00));
  plane.add(&rotor);
  //FloodFillDrawing planeFill(7, 6, 0, 0, 20, 20, plane, 0x00, 0xFF, 0x00);

  plane.translate(frameBuffer.getWidth()/2, 0);

  int time = 0;

  do {
    frameBuffer.fill(frameBuffer.getColor(0x00, 0x00, 0x00));

    bullets_center.draw(frameBuffer);
    bullets_left.draw(frameBuffer);
    bullets_right.draw(frameBuffer);
    plane.draw(frameBuffer);
    frameBuffer.swapBuffers();
    nanosleep(&delay, &rem);

    bullets_center.translate(0, -14);
    bullets_left.translate(-10, -10);
    bullets_right.translate(10, -10);
    plane.translate(-frameBuffer.getWidth()/2, 0);
    rotor.rotate(pi / 24);
    plane.scale(1.1, 1.1);
    plane.translate(frameBuffer.getWidth()/2, 0);
    ++time;
  }
  while (time < 100);

  std::cout << "\e[?25h" << std::flush;
  return 0;
}
