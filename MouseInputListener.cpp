#include "MouseInputListener.h"

MouseInputListener::MouseInputListener(int startX, int startY) : x(startX), y(startY) {
}

bool MouseInputListener::start() {
  device = open("/dev/input/mice", O_RDONLY | O_NONBLOCK);
  return device >= 0;
}

bool MouseInputListener::getInput() {
  char data[3];
  if (read(device, data, sizeof(data)) > 0) {
    left = data[0] & 0x1;
    right = data[0] & 0x2;
    middle = data[0] & 0x4;
    relativeX = data[1];
    relativeY = -data[2];
    x += relativeX;
    y += relativeY;
    
    return true;
  }
  else {
    return false;
  }
}

bool MouseInputListener::stop() {
  return close(device) >= 0;
}

int MouseInputListener::getX() {
  return x;
}

int MouseInputListener::getY() {
  return y;
}

int MouseInputListener::getRelativeX() {
  return relativeX;
}
  
int MouseInputListener::getRelativeY() {
  return relativeY;
}

bool MouseInputListener::isLeftClicked() {
  return left;
}

bool MouseInputListener::isRightClicked() {
  return right;
}

bool MouseInputListener::isMiddleClicked() {
  return middle;
}


