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
  d.add(new Line(0, 0, 100, 0, 0x00, 0xFF, 0x00));
  
  d.translate(100, 100);
  
  do {
    frameBuffer.fill(frameBuffer.getColor(0xFF, 0xFF, 0xFF));
    
    d.draw(frameBuffer);
    frameBuffer.swapBuffers();
    nanosleep(&delay, &rem);
    
    d.translate(-100, -100);
    d.rotate(pi / 12);
    d.translate(100, 100);
  }
  while (true);
  
  std::cout << "\e[?25h" << std::flush;
  return 0;
}
