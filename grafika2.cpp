#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include "Line.h"
#include "Drawing.h"
#include "CharBuilder.h"

int main() {
  std::cout << "\e[?25l" << std::flush;
  
  FrameBuffer frameBuffer("/dev/fb0");
  
  
  /*Drawing drawing1(100, 0);
  drawing1.add(new Line(0, 0, 100, 100, 0xFF, 0xFF, 0xFF));
  drawing1.add(new Line(100, 0, 100, 100, 0xFF, 0xFF, 0xFF));
  drawing1.add(new Line(0, 0, 100, 0, 0xFF, 0xFF, 0xFF));
  
  Drawing drawing2(200, 0);
  drawing2.add(new Line(0, 0, 100, 100, 0xFF, 0xFF, 0xFF));
  drawing2.add(new Line(100, 0, 100, 100, 0xFF, 0xFF, 0xFF));
  drawing2.add(new Line(0, 0, 100, 0, 0xFF, 0xFF, 0xFF));*/

  
  //drawing.add(&drawing1);
  //drawing.add(&drawing2);
  //drawing.add(BuildChar(350, 0, "font/a.txt", 80, 100, 0xFF, 0x00, 0x00));
  
  Drawing drawing(0, frameBuffer.getHeight());
  
  int letter_width = 70;
  int letter_height = 90;
  std::map<char, Drawing *> letters;
  for (char c = 'a'; c <= 'u'; ++c) {
    std::stringstream font_file;
    font_file << "font/" << c << ".txt";
    letters[c] = BuildChar(0, 0, font_file.str().c_str(), letter_width, letter_height, 0xFF, 0x00, 0x00);
  }
  
  std::string text = "abcde fg\na";
  int x = 0;
  int y = 0;
  int width = 80;
  int height = 100;
  for (auto& c : text) {
    if (c == '\n') {
      x = 0;
      y += height;
    }
    else if (c == ' ') {
      x += width;
    }
    else {
      Drawable *letter = letters[c]->clone();
      letter->transform(x, y);
      drawing.add(letter);
      x += width;
    }
  }
  
  
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
