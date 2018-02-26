#include <iostream>
#include <ctime>
#include "Line.h"
#include "FloodFillDrawing.h"

int main() {
  std::cout << "\e[?25l" << std::flush;
  
  FrameBuffer frameBuffer("/dev/fb0");
  frameBuffer.fill(frameBuffer.getColor(0x00, 0x00, 0x00));
  
  Drawing drawing(0, 0);
  drawing.add(new Line(20, 0, 59, 0, 0x00, 0xFF, 0x00));
  drawing.add(new Line(59, 0, 59, 39, 0x00, 0xFF, 0x00));
  drawing.add(new Line(59, 39, 27, 39, 0x00, 0xFF, 0x00));
  drawing.add(new Line(27, 39, 27, 79, 0x00, 0xFF, 0x00));
  drawing.add(new Line(27, 79, 20, 79, 0x00, 0xFF, 0x00));
  drawing.add(new Line(20, 79, 20, 0, 0x00, 0xFF, 0x00));
  drawing.add(new Line(27, 7, 52, 7, 0x00, 0xFF, 0x00));
  drawing.add(new Line(52, 7, 52, 32, 0x00, 0xFF, 0x00));
  drawing.add(new Line(52, 32, 27, 32, 0x00, 0xFF, 0x00));
  drawing.add(new Line(27, 32, 27, 7, 0x00, 0xFF, 0x00));
  
  Drawing drawing2(0, 0);
  drawing2.add(new Line(20, 0, 52, 0, 0x00, 0xFF, 0x00));
  drawing2.add(new Line(52, 0, 59, 7, 0x00, 0xFF, 0x00));
  drawing2.add(new Line(59, 7, 59, 72, 0x00, 0xFF, 0x00));
  drawing2.add(new Line(59, 72, 52, 79, 0x00, 0xFF, 0x00));
  drawing2.add(new Line(52, 79, 20, 79, 0x00, 0xFF, 0x00));
  drawing2.add(new Line(20, 79, 20, 0, 0x00, 0xFF, 0x00));
  drawing2.add(new Line(27, 7, 45, 7, 0x00, 0xFF, 0x00));
  drawing2.add(new Line(45, 7, 52, 14, 0x00, 0xFF, 0x00));
  drawing2.add(new Line(52, 14, 52, 65, 0x00, 0xFF, 0x00));
  drawing2.add(new Line(52, 65, 45, 72, 0x00, 0xFF, 0x00));
  drawing2.add(new Line(45, 72, 27, 72, 0x00, 0xFF, 0x00));
  drawing2.add(new Line(27, 72, 27, 7, 0x00, 0xFF, 0x00));
  
  Drawing drawing3(0, 0);
  drawing3.add(new Line(10, 0, 20, 0, 0x00, 0xFF, 0x00));
  drawing3.add(new Line(20, 0, 20, 10, 0x00, 0xFF, 0x00));
  drawing3.add(new Line(20, 10, 30, 10, 0x00, 0xFF, 0x00));
  drawing3.add(new Line(30, 10, 30, 20, 0x00, 0xFF, 0x00));
  drawing3.add(new Line(30, 20, 20, 20, 0x00, 0xFF, 0x00));
  drawing3.add(new Line(20, 20, 20, 40, 0x00, 0xFF, 0x00));
  drawing3.add(new Line(20, 40, 30, 40, 0x00, 0xFF, 0x00));
  drawing3.add(new Line(30, 40, 30, 50, 0x00, 0xFF, 0x00));
  drawing3.add(new Line(30, 50, 10, 50, 0x00, 0xFF, 0x00));
  drawing3.add(new Line(10, 50, 10, 20, 0x00, 0xFF, 0x00));
  drawing3.add(new Line(10, 20, 0, 20, 0x00, 0xFF, 0x00));
  drawing3.add(new Line(0, 20, 0, 10, 0x00, 0xFF, 0x00));
  drawing3.add(new Line(0, 10, 10, 10, 0x00, 0xFF, 0x00));
  drawing3.add(new Line(10, 10, 10, 0, 0x00, 0xFF, 0x00));
  
  Drawing drawing4(0, 0);
  drawing4.add(new Line(5, 0, 45, 0, 0x00, 0xFF, 0x00));
  drawing4.add(new Line(5, 0, 5, 10, 0x00, 0xFF, 0x00));
  drawing4.add(new Line(5, 10, 35, 10, 0x00, 0xFF, 0x00));
  drawing4.add(new Line(45, 0, 10, 45, 0x00, 0xFF, 0x00));
  drawing4.add(new Line(35, 10, 5, 50, 0x00, 0xFF, 0x00));
  drawing4.add(new Line(5, 50, 45, 50, 0x00, 0xFF, 0x00));
  drawing4.add(new Line(10, 45, 45, 45, 0x00, 0xFF, 0x00));
  
  Drawing drawing5(0, 0);
  drawing5.add(new Line(0, 0, 80, 0, 0x00, 0xFF, 0x00));
  drawing5.add(new Line(80, 0, 80, 8, 0x00, 0xFF, 0x00));
  drawing5.add(new Line(80, 8, 8, 8, 0x00, 0xFF, 0x00));
  drawing5.add(new Line(8, 8, 8, 72, 0x00, 0xFF, 0x00));
  drawing5.add(new Line(8, 72, 80, 72, 0x00, 0xFF, 0x00));
  drawing5.add(new Line(80, 72, 80, 80, 0x00, 0xFF, 0x00));
  drawing5.add(new Line(80, 80, 0, 80, 0x00, 0xFF, 0x00));
  drawing5.add(new Line(0, 80, 0, 0, 0x00, 0xFF, 0x00));
  
  Drawing drawing6(0, 0);
  drawing6.add(new Line(45, 45, 45, 50, 0x00, 0xFF, 0x00));
  drawing6.add(new Line(45, 50, 50, 50, 0x00, 0xFF, 0x00));
  drawing6.add(new Line(50, 50, 50, 45, 0x00, 0xFF, 0x00));
  drawing6.add(new Line(50, 45, 45, 45, 0x00, 0xFF, 0x00));
  
  Drawing drawinga(10, 10);
  drawinga.add(new Line(20, 0, 59, 0, 0xAA, 0x99, 0xAA));
  drawinga.add(new Line(59, 0, 59, 39, 0xAA, 0x99, 0xAA));
  drawinga.add(new Line(59, 39, 27, 39, 0xAA, 0x99, 0xAA));
  drawinga.add(new Line(27, 39, 27, 79, 0xAA, 0x99, 0xAA));
  drawinga.add(new Line(27, 79, 20, 79, 0xAA, 0x99, 0xAA));
  drawinga.add(new Line(20, 79, 20, 0, 0xAA, 0x99, 0xAA));
  drawinga.add(new Line(27, 7, 52, 7, 0xAA, 0x99, 0xAA));
  drawinga.add(new Line(52, 7, 52, 32, 0xAA, 0x99, 0xAA));
  drawinga.add(new Line(52, 32, 27, 32, 0xAA, 0x99, 0xAA));
  drawinga.add(new Line(27, 32, 27, 7, 0xAA, 0x99, 0xAA));
  
  Drawing drawing2a(10, 110);
  drawing2a.add(new Line(20, 0, 52, 0, 0x00, 0xFF, 0x00));
  drawing2a.add(new Line(52, 0, 59, 7, 0x00, 0xFF, 0x00));
  drawing2a.add(new Line(59, 7, 59, 72, 0x00, 0xFF, 0x00));
  drawing2a.add(new Line(59, 72, 52, 79, 0x00, 0xFF, 0x00));
  drawing2a.add(new Line(52, 79, 20, 79, 0x00, 0xFF, 0x00));
  drawing2a.add(new Line(20, 79, 20, 0, 0x00, 0xFF, 0x00));
  drawing2a.add(new Line(27, 7, 45, 7, 0x00, 0xFF, 0x00));
  drawing2a.add(new Line(45, 7, 52, 14, 0x00, 0xFF, 0x00));
  drawing2a.add(new Line(52, 14, 52, 65, 0x00, 0xFF, 0x00));
  drawing2a.add(new Line(52, 65, 45, 72, 0x00, 0xFF, 0x00));
  drawing2a.add(new Line(45, 72, 27, 72, 0x00, 0xFF, 0x00));
  drawing2a.add(new Line(27, 72, 27, 7, 0x00, 0xFF, 0x00));
  
  Drawing drawing3a(10, 210);
  drawing3a.add(new Line(10, 0, 20, 0, 0x00, 0xFF, 0x00));
  drawing3a.add(new Line(20, 0, 20, 10, 0x00, 0xFF, 0x00));
  drawing3a.add(new Line(20, 10, 30, 10, 0x00, 0xFF, 0x00));
  drawing3a.add(new Line(30, 10, 30, 20, 0x00, 0xFF, 0x00));
  drawing3a.add(new Line(30, 20, 20, 20, 0x00, 0xFF, 0x00));
  drawing3a.add(new Line(20, 20, 20, 40, 0x00, 0xFF, 0x00));
  drawing3a.add(new Line(20, 40, 30, 40, 0x00, 0xFF, 0x00));
  drawing3a.add(new Line(30, 40, 30, 50, 0x00, 0xFF, 0x00));
  drawing3a.add(new Line(30, 50, 10, 50, 0x00, 0xFF, 0x00));
  drawing3a.add(new Line(10, 50, 10, 20, 0x00, 0xFF, 0x00));
  drawing3a.add(new Line(10, 20, 0, 20, 0x00, 0xFF, 0x00));
  drawing3a.add(new Line(0, 20, 0, 10, 0x00, 0xFF, 0x00));
  drawing3a.add(new Line(0, 10, 10, 10, 0x00, 0xFF, 0x00));
  drawing3a.add(new Line(10, 10, 10, 0, 0x00, 0xFF, 0x00));
  
  Drawing drawing4a(10, 310);
  drawing4a.add(new Line(5, 0, 45, 0, 0x00, 0xFF, 0x00));
  drawing4a.add(new Line(5, 0, 5, 10, 0x00, 0xFF, 0x00));
  drawing4a.add(new Line(5, 10, 35, 10, 0x00, 0xFF, 0x00));
  drawing4a.add(new Line(45, 0, 10, 45, 0x00, 0xFF, 0x00));
  drawing4a.add(new Line(35, 10, 5, 50, 0x00, 0xFF, 0x00));
  drawing4a.add(new Line(5, 50, 45, 50, 0x00, 0xFF, 0x00));
  drawing4a.add(new Line(10, 45, 45, 45, 0x00, 0xFF, 0x00));
  
  Drawing drawing5a(10, 410);
  drawing5a.add(new Line(0, 0, 80, 0, 0x00, 0xFF, 0x00));
  drawing5a.add(new Line(80, 0, 80, 8, 0x00, 0xFF, 0x00));
  drawing5a.add(new Line(80, 8, 8, 8, 0x00, 0xFF, 0x00));
  drawing5a.add(new Line(8, 8, 8, 72, 0x00, 0xFF, 0x00));
  drawing5a.add(new Line(8, 72, 80, 72, 0x00, 0xFF, 0x00));
  drawing5a.add(new Line(80, 72, 80, 80, 0x00, 0xFF, 0x00));
  drawing5a.add(new Line(80, 80, 0, 80, 0x00, 0xFF, 0x00));
  drawing5a.add(new Line(0, 80, 0, 0, 0x00, 0xFF, 0x00));
  
  Drawing drawing6a(10, 510);
  drawing6a.add(new Line(45, 45, 45, 50, 0x00, 0xFF, 0x00));
  drawing6a.add(new Line(45, 50, 50, 50, 0x00, 0xFF, 0x00));
  drawing6a.add(new Line(50, 50, 50, 45, 0x00, 0xFF, 0x00));
  drawing6a.add(new Line(50, 45, 45, 45, 0x00, 0xFF, 0x00));
  
  FloodFillDrawing floodFillDrawing(10, 10, 80, 80, frameBuffer, drawing, 21, 1, 0x00, 0xFF, 0x00);
  floodFillDrawing.draw(frameBuffer);
  drawinga.draw(frameBuffer);
  
  
  FloodFillDrawing floodFillDrawing2(10, 110, 80, 80, frameBuffer, drawing2, 21, 1, 0x00, 0xFF, 0x00);
  floodFillDrawing2.draw(frameBuffer);
  
  FloodFillDrawing floodFillDrawing3(10, 210, 50, 50, frameBuffer, drawing3, 15, 15, 0x00, 0xFF, 0x00);
  floodFillDrawing3.draw(frameBuffer);
  
  FloodFillDrawing floodFillDrawing4(10, 310, 50, 50, frameBuffer, drawing4, 5, 1, 0x00, 0xFF, 0x00);
  floodFillDrawing4.draw(frameBuffer);
    
  FloodFillDrawing floodFillDrawing5(10, 410, 80, 80, frameBuffer, drawing5, 2, 2, 0x00, 0xFF, 0x00);
  floodFillDrawing5.draw(frameBuffer);
  
  FloodFillDrawing floodFillDrawing6(10, 510, 50, 50, frameBuffer, drawing6, 47, 47, 0x00, 0xFF, 0x00);
  floodFillDrawing6.draw(frameBuffer);
  
  frameBuffer.swapBuffers();
  
  timespec delay, rem;
  delay.tv_sec = 5;
  delay.tv_nsec = 0;
  nanosleep(&delay, &rem);
  
  std::cout << "\e[?25h" << std::flush;
  return 0;
}
