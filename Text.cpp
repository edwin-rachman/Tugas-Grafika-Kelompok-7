#include "Text.h"

Text::Text (const char *file_path, int x, int y, std::string text) : x(x), y(y), drawing(x, y) {
  std::fstream input(file_path);
  
  int count;
  input >> count;
  input >> width;
  input >> height;
  
  for (int i = 0; i < count; ++i) {
    char c;
    int n;
    input >> c;
    input >> n;
    letters[c] = new Drawing(0, 0);
    
    for (int j = 0; j < n; ++j) {
      int x_0, y_0, x_1, y_1;
      input >> x_0;
      input >> y_0;
      input >> x_1;
      input >> y_1;
      
      letters[c]->add(new Line(x_0, y_0, x_1, y_1, 0xFF, 0xFF, 0xFF));
    }
  } 
  
  set(text);
}

Text::Text (const Text& text) {
  width = text.width;
  height = text.height;
  x = text.x;
  y = text.y;
  letters = text.letters;
  drawing = drawing.clone();
}

void Text::set (std::string text) {
  for (auto& c : s) {
    if (c == '\n') {
      x = 0;
      y += height;
    }
    else {
      Drawable *letter = letters[c].clone();
      letter->transform(x, y);
      drawing.add(letter);
      x += width;
    }
  }
}

void Text::draw (FrameBuffer& frameBuffer) {
  drawing.draw(frameBuffer);
}

void Text::transform (int d_x, int d_y) {
  x += d_x;
  y += d_y;
  drawing.transform(d_x, d_y);
}

Drawable *Text::clone () {
  return new Text(*this);
}
