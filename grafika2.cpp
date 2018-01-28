#include <ctime>
#include <fstream>
#include <iostream>
#include "Line.h"
#include "Drawing.h"

int main() {
  std::cout << "\e[?25l" << std::flush;
  
  FrameBuffer frameBuffer("/dev/fb0");
  
  
  Drawing drawing1(100, 0);
  drawing1.add(new Line(0, 0, 100, 100, 0xFF, 0xFF, 0xFF));
  drawing1.add(new Line(100, 0, 100, 100, 0xFF, 0xFF, 0xFF));
  drawing1.add(new Line(0, 0, 100, 0, 0xFF, 0xFF, 0xFF));
  
  Drawing drawing2(200, 0);
  drawing2.add(new Line(0, 0, 100, 100, 0xFF, 0xFF, 0xFF));
  drawing2.add(new Line(100, 0, 100, 100, 0xFF, 0xFF, 0xFF));
  drawing2.add(new Line(0, 0, 100, 0, 0xFF, 0xFF, 0xFF));
  
  Drawing drawing(0, frameBuffer.getHeight());
  drawing.add(&drawing1);
  drawing.add(&drawing2);
  
  timespec delay, rem;
  delay.tv_sec = 0;
  delay.tv_nsec = 33333333L;
  
  do {
    frameBuffer.fill(0x00, 0x00, 0x00);
    drawing.draw(frameBuffer);
    frameBuffer.swapBuffers();
    nanosleep(&delay, &rem);
    
    drawing.transform(0, -5);
  }
  while (drawing.getY() > 0);
  
  std::cout << "\e[?25h" << std::flush;
  return 0;
}
