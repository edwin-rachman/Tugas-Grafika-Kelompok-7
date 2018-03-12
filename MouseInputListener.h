#ifndef MOUSEINPUTLISTENER_H
#define MOUSEINPUTLISTENER_H

#include <unistd.h>
#include <fcntl.h>

class MouseInputListener {
private:
  int device = -1;
  int x = 0;
  int y = 0;
  int relativeX = 0;
  int relativeY = 0;
  bool left = false;
  bool right = false;
  bool middle = false;
  
public:
  MouseInputListener();
  MouseInputListener(int startX, int startY);
  bool start();
  bool getInput();
  bool stop();
  
  int getX();
  int getY();
  int getRelativeX();
  int getRelativeY();
  bool isLeftClicked();
  bool isRightClicked();
  bool isMiddleClicked();
};

#endif
