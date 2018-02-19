#ifndef POLYGON_H
#define POLYGON_H

#include <tuple>
#include <map>
#include <vector>
#include "Line.h"

class Polygon : public Drawable {
  std::map<char, Point> vertices;
  std::vector<std::tuple<char, char, Line>> edges;
  
  void addVertex(char v, float x, float y);
  void addEdge(char v0, char v1);
  void draw(FrameBuffer& frameBuffer);
  void translate(float translate_x, float translate_y);
  void scale(float scale_x, float scale_y, float origin_x, float origin_y);
  void rotate(float angle, float origin_x, float origin_y);
  Drawable *clone();
};

#endif POLYGON_H
