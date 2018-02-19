#include "Polygon.h"



Polygon::Polygon(const Polygon& polygon) {
  for (auto& pair : polygon.vertices) {
    vertices[pair.first] = Point(pair.second);
  }
  
  for (auto& tuple : polygon.edges) {
    edges.push_back(std::make_tuple(tuple.first, tuple.second, Line(vertices[tuple.first], vertices[tuple.second])));
  }
}

void Polygon::addVertex(char v, float x, float y) {
  vertices[v] = Point(x, y);
}

void Polygon::addEdge(char v0, char v1) {
  edges.push_back(std::make_tuple(v0, v1, Line(vertices[v0], vertices[v1])));
}

void Polygon::draw(FrameBuffer& frameBuffer) {
}

void Polygon::translate(float translate_x, float translate_y) {
  for (auto& tuple : edges) {
    tuple.third.translate(translate_x, translate_y);
  }
}

void Polygon::scale(float scale_x, float scale_y, float origin_x, float origin_y) {
  for (auto& tuple : edges) {
    tuple.third.scale(scale_x, scale_y, origin_x, origin_y);
  }
}

void Polygon::rotate(float angle, float origin_x, float origin_y) {
  for (auto& tuple : edges) {
    tuple.third.translate(angle, origin_x, origin_y);
  }
}

Drawable Polygon::*clone() {
  return new Polygon(*this);
}
