#include <ctime>
#include <fstream>
#include <iostream>
<<<<<<< HEAD
#include <sstream>
#include <map>
#include "Line.h"
#include "Drawing.h"
#include "CharBuilder.h"
=======
#include <map>
#include "Line.h"
#include "Drawing.h"
#include "Text.h"

>>>>>>> new

int main() {
  std::cout << "\e[?25l" << std::flush;
  Text text("letter.txt", 0, 100, "AAA");
  FrameBuffer frameBuffer("/dev/fb0");
<<<<<<< HEAD
  Drawing text(0, frameBuffer.getHeight());
  
  int letter_width = 25;
  int letter_height = 35;
  std::map<char, Drawing *> letters;
  for (char c = 'a'; c <= 'z'; ++c) {
    std::stringstream font_file;
    font_file << "font/" << c << ".txt";
    letters[c] = BuildChar(0, 0, font_file.str().c_str(), letter_width, letter_height, 0x00, 0xFF, 0x00);
  }
  
  std::string text_str = "tugas grafika komputer dua\nkelompok tujuh\nnursyahrina\nfarhan makarim\nm rizki duwinanto\nedwin rachman\nprama legawa halqavi\nsuhendi\nlouis leslie";
  int x = 0;
  int y = 0;
  int width = 30;
  int height = 40;
  for (auto& c : text_str) {
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
      text.add(letter);
      x += width;
    }
  }
  
  Drawing plane = *(BuildChar(-150, frameBuffer.getHeight() / 2 - 50, "font/plane.txt", 150, 100, 0x00, 0x00, 0xFF));
  
  Drawing bullets_center(frameBuffer.getWidth() / 2, frameBuffer.getHeight());
  Drawing bullets_left(frameBuffer.getWidth() / 2, frameBuffer.getHeight());
  Drawing bullets_right(frameBuffer.getWidth() / 2, frameBuffer.getHeight());
  for (int i = 0; i < 50; ++i) {
    bullets_center.add(new Line(0, i * 50, 0, i * 50 + 14, 0xFF, 0x00, 0x00));
    bullets_left.add(new Line(i * 40, i * 40, i * 40 + 10, i * 40 + 10, 0xFF, 0x00, 0x00));
    bullets_right.add(new Line(-i * 40, i * 40, -i * 40 - 10, i * 40 + 10, 0xFF, 0x00, 0x00));
  }
=======

  
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
>>>>>>> new
  
  timespec delay, rem;
  delay.tv_sec = 0;
  delay.tv_nsec = 33333333L;
  do {
    frameBuffer.fill(0x00, 0x00, 0x00);
    text.draw(frameBuffer);
    bullets_center.draw(frameBuffer);
    bullets_left.draw(frameBuffer);
    bullets_right.draw(frameBuffer);
    plane.draw(frameBuffer);
    
    frameBuffer.swapBuffers();
    nanosleep(&delay, &rem);
    text.transform(0, -5);
    bullets_center.transform(0, -14);
    bullets_left.transform(-10, -10);
    bullets_right.transform(10, -10);
    plane.transform(10, 0);
  }
  while (text.getY() > 0);
  
  std::cout << "\e[?25h" << std::flush;
  return 0;
}
