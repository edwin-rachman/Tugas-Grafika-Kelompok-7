#include <iostream>
#include <ctime>
#include "Line.h"
#include "Drawing.h"

const float pi = std::acos(-1);

int main() {
  std::cout << "\e[?25l" << std::flush;
  FrameBuffer frameBuffer("/dev/fb0");

  timespec delay, rem;
  delay.tv_sec = 1;
  delay.tv_nsec = 0;

  Drawing d(0, 0);
  Drawing x(frameBuffer.getWidth()/2, frameBuffer.getHeight()/2);
  d.add(new Line(0, 0, 100, 0, 0x00, 0xFF, 0x00));

  x.add(new Line(0, 4, 7, 5, 0x00, 0xFF, 0x00));
  x.add(new Line(7, 5, 8, 7, 0x00, 0xFF, 0x00));
  x.add(new Line(8, 7, 10, 7, 0x00, 0xFF, 0x00));
  x.add(new Line(10, 7, 11, 5, 0x00, 0xFF, 0x00));
  x.add(new Line(11, 5, 18, 5, 0x00, 0xFF, 0x00));
  x.add(new Line(18, 5, 11, 3, 0x00, 0xFF, 0x00));
  x.add(new Line(11, 3, 9, 0, 0x00, 0xFF, 0x00));
  x.add(new Line(9, 0, 7, 3, 0x00, 0xFF, 0x00));
  x.add(new Line(7, 3, 0, 5, 0x00, 0xFF, 0x00));

  d.translate(100, 100);

  do {
    frameBuffer.fill(frameBuffer.getColor(0xFF, 0xFF, 0xFF));

    d.draw(frameBuffer);
    x.draw(frameBuffer);
    frameBuffer.swapBuffers();
    nanosleep(&delay, &rem);

    x.scale(100, 100);
    d.translate(-100, -100);
    d.rotate(pi / 12);
    d.translate(100, 100);
  }
  while (true);

  std::cout << "\e[?25h" << std::flush;
  return 0;
}
