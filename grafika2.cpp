#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include "Line.h"
#include "Drawing.h"
#include "Text.h"


int main() {
  std::cout << "\e[?25l" << std::flush;
  Text text("letter.txt", 0, 100, "AAA");
  FrameBuffer frameBuffer("/dev/fb0");

  
  /*
  Drawing drawing1(100, 0);
  drawing1.add(new Line(0, 0, 100, 100, 0xFF, 0xFF, 0xFF));
  drawing1.add(new Line(100, 0, 100, 100, 0xFF, 0xFF, 0xFF));
  drawing1.add(new Line(0, 0, 100, 0, 0xFF, 0xFF, 0xFF));
  
  Drawable *drawing2 = drawing1.clone();
  drawing2->transform(100, 0);
  
  Drawing drawing(0, frameBuffer.getHeight());
  drawing.add(&drawing1);
  drawing.add(drawing2);*/
  
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
  while (text.getY() > 0);
  
  std::cout << "\e[?25h" << std::flush;
  return 0;
}
