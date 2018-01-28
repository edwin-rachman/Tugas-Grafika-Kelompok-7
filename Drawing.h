#ifndef DRAWING_H
#define DRAWING_H

#include <cstdint>
#include <vector>
#include "Drawable.h"

class Drawing : public Drawable {
private:
  int x;
  int y;
  std::vector<Drawable *> drawables;
  
public:
  Drawing (int x, int y);
  Drawing (const Drawing& drawing);
  Drawable *clone ();
  ~Drawing ();
  void add (Drawable *drawable);
  void draw (FrameBuffer& frameBuffer);
  void transform (int d_x, int d_y);
  int getX ();
  int getY ();
};

#endif
