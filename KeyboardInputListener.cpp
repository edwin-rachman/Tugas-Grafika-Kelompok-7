#include "KeyboardInputListener.h"

termios KeyboardInputListener::oldTermios;
termios KeyboardInputListener::newTermios;

KeyboardInputListener::KeyboardInputListener(long delaySeconds, long delayMicroseconds) {
  delay.tv_sec = delaySeconds;
  delay.tv_usec = delayMicroseconds;
}

void KeyboardInputListener::stop() {
  tcsetattr(0, TCSANOW, &oldTermios);
}

void KeyboardInputListener::start() {
  tcgetattr(0, &oldTermios);
  memcpy(&newTermios, &oldTermios, sizeof(newTermios));
  atexit(stop);
  cfmakeraw(&newTermios);
  tcsetattr(0, TCSANOW, &newTermios);
}

int KeyboardInputListener::receivedInput() {
  timeval timeout = delay;
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(0, &fds);
  return select(1, &fds, NULL, NULL, &timeout);
}

int KeyboardInputListener::getInput() {
  int r;
  unsigned char c;
  if ((r = read(0, &c, sizeof(c))) < 0) {
    return r;
  } 
  else {
    return c;
  }
}
