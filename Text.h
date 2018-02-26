#ifndef TEXT_H
#define TEXT_H

#include <fstream>
#include <string>
#include <map>
#include "Line.h"
#include "Drawing.h"

class Text : public Drawable {
public:
  int width;
  int height;
  int x;
  int y;
  std::map<char, Drawing *> letters;
  Drawing drawing;

public:
  Text (const char *file_path, int x, int y);
  Text (const Text& text);
  void set (std::string text);
  void draw (FrameBuffer& frameBuffer);
  void transform (int d_x, int d_y);
  Drawable *clone ();
};

#endif
